using JuMP, GLPK

n = 0
m = 0
weights = zeros(n, n)
costs = zeros(n, n)
T_max = 0

filename = "data2.txt"

open(filename) do io
    global n = parse(Int, readline(io))
    global m = parse(Int, readline(io))
    global T_max = parse(Int, readline(io))
    
    global weights = zeros(n, n)
    global costs = zeros(n, n)

    for _ in 1:m
        from, to, weight, cost = split(readline(io))
        from, to, weight, cost = parse(Int, from), parse(Int, to), parse(Int, weight), parse(Int, cost)
        
        global weights[from, to] = weight
        global costs[from, to] = cost
    end
end

b = zeros(n)
b[1] = 1
b[10] = -1

shortest_path = Model()
set_optimizer(shortest_path, GLPK.Optimizer)

@variable(shortest_path, x[1:n, 1:n], Bin)

@constraint(shortest_path, [i = 1:n, j = 1:n; weights[i, j] == 0], x[i, j] == 0)

@constraint(shortest_path, [i = 1:n], sum(x[i, :]) - sum(x[:, i]) == b[i])

@constraint(shortest_path, sum(costs[i, j] * x[i, j] for i in 1:n, j in 1:n) <= T_max)

@objective(shortest_path, Min, sum(weights .* x))

optimize!(shortest_path)

println(objective_value(shortest_path))
for i in 1:n
    for j in 1:n
        print(value.(x[i, j]), " ")
    end
    println()
end