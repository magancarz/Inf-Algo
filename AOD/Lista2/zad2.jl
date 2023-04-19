using JuMP, GLPK

nodes = 0
edges = 0

filename = "data.txt"
lines = filter(line -> !isempty(strip(line)), readlines(filename))
nodes, edges = split(lines[1])
nodes, edges = parse(Int, nodes), parse(Int, edges)
c = zeros(nodes, nodes)
u = zeros(nodes, nodes)
t_max = 10

for i in 2:edges+1
    from, to, cap, cost = split(lines[i])
    from, to, cap, cost = parse(Int, from), parse(Int, to), parse(Int, cap), parse(Int, cost)
    c[from, to] = cap
    u[from, to] = cost
end

n = nodes
b = zeros(nodes)
b[1] = 1
b[13] = -1
T_max = 24
shortest_path = Model()
set_optimizer(shortest_path, GLPK.Optimizer)
set_silent(shortest_path)
@variable(shortest_path, x[1:n, 1:n], Bin)
@constraint(shortest_path, [i = 1:n, j = 1:n; c[i, j] == 0], x[i, j] == 0)
@constraint(shortest_path, [i = 1:n], sum(x[i, :]) - sum(x[:, i]) == b[i])
@constraint(shortest_path, sum(u[i, j] * x[i, j] for i in 1:n, j in 1:n) <= T_max)
@objective(shortest_path, Min, sum(c .* x))
optimize!(shortest_path)
println(objective_value(shortest_path))
for i in 1:n
    for j in 1:n
        print(value.(x[i,j]), " ")
    end
    println()
end