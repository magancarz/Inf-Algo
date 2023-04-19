using JuMP
using GLPK

num_of_materials = 0
num_of_machines = 0
hours_constraints::Vector{Int64} = []
materials_constraints::Vector{Int64}  = []
minutes_per_kg::Vector{Int64} = []
costs::Vector{Int64} = []
profits::Vector{Int64} = []
machine_costs::Vector{Int64} = []

open("data.txt") do io
    while !eof(io)
        global num_of_machines = parse(Int,readline(io))
        
        global num_of_materials = parse(Int,readline(io))
        for i in 1:num_of_machines
            push!(hours_constraints, parse(Int64, readline(io)))
        end
        for i in 1:num_of_materials
            push!(materials_constraints, parse(Int64,readline(io)))
        end
        for i in 1:num_of_materials*num_of_machines
            push!(minutes_per_kg, parse(Int64, readline(io)))
        end
        for i in 1:num_of_materials
            push!(profits, parse(Int64,readline(io)))
        end
        for i in 1:num_of_materials
            push!(costs, parse(Int64,readline(io)))
        end
        for i in 1:num_of_machines
            push!(machine_costs, parse(Int64, readline(io)))
        end
    end
end

println(hours_constraints)
println(materials_constraints)
println(minutes_per_kg)
println(profits)
println(costs)
println(machine_costs)


szycie = Model()
set_optimizer(szycie,GLPK.Optimizer)

@variable(szycie, x[1:num_of_materials] >=0)


for i in 1:num_of_materials
    @constraint(szycie, x[i]<=materials_constraints[i])
end

for i in 1:num_of_machines
    @constraint(szycie, sum(minutes_per_kg[((i-1)*num_of_materials)+j]*x[j] for j in 1:num_of_materials)<=hours_constraints[i])
end

@objective(szycie, Max, sum(x[i]*(profits[i]-costs[i]) for i in 1:num_of_materials) - 
            sum((minutes_per_kg[((i-1)*num_of_materials)+j]*x[j]*machine_costs[i])/60 for j in 1:num_of_materials, i in 1:num_of_machines))



optimize!(szycie)


println("value: ", objective_value(szycie))

for i in 1:num_of_materials
    println("x", i, " = ", value.(x[i]))
end
