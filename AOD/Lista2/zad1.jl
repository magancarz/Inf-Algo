using JuMP
using GLPK

n = 0
m = 0
companies_constraints = Int[]
airports_constraints = Int[]
costs = Int[]

filename = "data1.txt"

open(filename) do io
    global n = parse(Int, readline(io))
    global companies_constraints = [parse(Int64, readline(io)) for _ in 1:n]
    global m = parse(Int, readline(io))
    global airports_constraints = [parse(Int64, readline(io)) for _ in 1:m]
    global costs = [parse(Int64, readline(io)) for _ in 1:n * m]
end

println(n)
println(m)
println(companies_constraints)
println(costs)
println(airports_constraints)

airports = Model(optimizer_with_attributes(GLPK.Optimizer))

@variable(airports, x[1:n, 1:m] >= 0)

@constraint(airports, [i=1:n], sum(x[i,1:m]) <= companies_constraints[i])
@constraint(airports, [i=1:m], sum(x[1:n,i]) >= airports_constraints[i])

@objective(airports, Min, sum(costs[((i - 1) * m) + j] * x[i, j] for i in 1:n, j in 1:m))

optimize!(airports)

println("Minimalny koszt: ", objective_value(airports))
for j in 1:n
    for i in 1:m
        println("x[", j, ",", i, "] = ", value(x[j, i]))
    end
end