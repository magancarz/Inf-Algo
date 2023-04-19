using JuMP
using GLPK

num_of_shifts = 0
num_of_districts = 0
shifts_constraints::Vector{Int64} = []
districts_constraints::Vector{Int64}  = []
lower_constraints::Vector{Int64} = []
upper_constraints::Vector{Int64} = []

open("data.txt") do io
    while !eof(io)
        global num_of_shifts = parse(Int,readline(io))
        
        global num_of_districts = parse(Int,readline(io))
        for i in 1:num_of_shifts
            push!(shifts_constraints, parse(Int64, readline(io)))
        end
        for i in 1:num_of_districts
            push!(districts_constraints, parse(Int64,readline(io)))
        end
        for i in 1:num_of_shifts*num_of_districts
            push!(lower_constraints, parse(Int64, readline(io)))
        end
        for i in 1:num_of_shifts*num_of_districts
            push!(upper_constraints, parse(Int64,readline(io)))
        end
    end
end

println(shifts_constraints)
println(districts_constraints)
println(lower_constraints)
println(upper_constraints)


policja = Model()
set_optimizer(policja,GLPK.Optimizer)

@variable(policja, x[1:num_of_shifts*num_of_districts] >=0)


for i in 1:num_of_shifts*num_of_districts
    @constraint(policja, upper_constraints[i]>=x[i]>=lower_constraints[i])
end

for i in 1:num_of_shifts
    @constraint(policja, sum(x[((i-1)*num_of_districts)+j] for j in 1:num_of_districts)>=shifts_constraints[i])
end

for i in 1:num_of_districts
    @constraint(policja, sum(x[((j-1)*num_of_districts)+i] for j in 1:num_of_shifts)>=districts_constraints[i])
end

@objective(policja, Min, sum(x[i] for i in 1:num_of_districts*num_of_shifts) )

optimize!(policja)

println("value: ", objective_value(policja))

for i in 1:num_of_districts*num_of_shifts
    println("x", i, " = ", value.(x[i]))
end


