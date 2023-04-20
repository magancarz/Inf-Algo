using JuMP
using GLPK

n = 0
m = 0
c = 0
k = 0
containers_grid = zeros(n, m)

filename = "data4.txt"

open(filename) do io
    global n = parse(Int, readline(io))
    global m = parse(Int, readline(io))
    global c = parse(Int, readline(io))
    global k = parse(Int, readline(io))

    global containers_grid = zeros(n, m)

    for _ in 1:c
        x, y = split(readline(io))
        x, y = parse(Int, x), parse(Int, y)

        global containers_grid[x, y] = 1
    end
end

println(n)
println(m)
println(c)
println(k)
println(containers_grid)

model = Model(GLPK.Optimizer)

@variable(model, x[1:n, 1:m], Bin)

for i in 1:n
    for j in 1:m
        if containers_grid[i, j] == 1
            @constraint(model, x[i, j] == 0)
            @constraint(model, sum(x[i, max(j - k, 1):min(j + k, m)]) + sum(x[max(i - k, 1):min(i + k, n), j]) >= 1)
        end
    end
end

@objective(model, Min, sum(x))

optimize!(model)

println("Cameras count: ", objective_value(model))
for i in 1:n
    for j in 1:m
        if value(x[i,j]) > 0.5
            println("Camera on position ($i,$j)")
        end
    end
end