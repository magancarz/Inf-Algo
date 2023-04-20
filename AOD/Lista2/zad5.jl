using JuMP
using GLPK

materials_count = 0
machines_count = 0
hours_constraints = []
materials_constraints  = []
minutes_per_kg = []
costs = []
profits = []
machine_costs = []

open("data5.txt") do io
    global materials_count = parse(Int, readline(io))
    global machines_count = parse(Int, readline(io))
    
    for _ in 1:machines_count
        push!(hours_constraints, parse(Int, readline(io)))
    end
    
    for _ in 1:materials_count
        push!(materials_constraints, parse(Int, readline(io)))
    end
    
    for _ in 1:materials_count * machines_count
        push!(minutes_per_kg, parse(Int, readline(io)))
    end
    
    for _ in 1:materials_count
        push!(profits, parse(Int, readline(io)))
    end
    
    for _ in 1:materials_count
        push!(costs, parse(Int, readline(io)))
    end
    
    for _ in 1:machines_count
        push!(machine_costs, parse(Int, readline(io)))
    end
end

println(hours_constraints)
println(materials_constraints)
println(minutes_per_kg)
println(profits)
println(costs)
println(machine_costs)

wedzarnia = Model()
set_optimizer(wedzarnia, GLPK.Optimizer)

@variable(wedzarnia, x[1:materials_count] >= 0)

for i in 1:materials_count
    @constraint(wedzarnia, x[i] <= materials_constraints[i])
end

for i in 1:machines_count
    @constraint(wedzarnia, sum(minutes_per_kg[((i - 1) * materials_count) + j] * x[j] for j in 1:materials_count) <= hours_constraints[i])
end

@objective(wedzarnia, Max,
    sum(x[i] * (profits[i] - costs[i]) for i in 1:materials_count) - 
    sum((minutes_per_kg[((i - 1) * materials_count) + j] * x[j] * machine_costs[i]) / 60.0 
    for j in 1:materials_count, i in 1:machines_count))

optimize!(wedzarnia)

println("Profit: ", objective_value(wedzarnia))

for i in 1:materials_count
    println("x", i, " = ", value.(x[i]))
end
