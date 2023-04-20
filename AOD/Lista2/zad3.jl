using JuMP
using GLPK

shifts_count = 0
districts_count = 0
shifts_constraints = []
districts_constraints = []
lower_constraints = []
upper_constraints = []

open("data3.txt") do io
    global shifts_count = parse(Int, readline(io))
    
    global districts_count = parse(Int, readline(io))
    
    for i in 1:shifts_count
        push!(shifts_constraints, parse(Int, readline(io)))
    end
    
    for i in 1:districts_count
        push!(districts_constraints, parse(Int, readline(io)))
    end
    
    for i in 1:shifts_count * districts_count
        push!(lower_constraints, parse(Int, readline(io)))
    end
    
    for i in 1:shifts_count * districts_count
        push!(upper_constraints, parse(Int, readline(io)))
    end
end

println(shifts_count)
println(districts_count)
println(shifts_constraints)
println(districts_constraints)
println(lower_constraints)
println(upper_constraints)

police_helper = Model()
set_optimizer(police_helper,GLPK.Optimizer)

@variable(police_helper, x[1:shifts_count * districts_count] >=0)


for i in 1:shifts_count * districts_count
    @constraint(police_helper, upper_constraints[i] >= x[i] >= lower_constraints[i])
end

for i in 1:shifts_count
    @constraint(police_helper, sum(x[((i - 1) * districts_count) + j] for j in 1:districts_count) >= shifts_constraints[i])
end

for i in 1:districts_count
    @constraint(police_helper, sum(x[((j - 1) * districts_count) + i] for j in 1:shifts_count) >= districts_constraints[i])
end

@objective(police_helper, Min, sum(x[i] for i in 1:districts_count * shifts_count) )

optimize!(police_helper)

println("Minimal count of radiowozes: ", objective_value(police_helper))

for i in 1:districts_count * shifts_count
    println("x", i, " = ", value.(x[i]))
end


