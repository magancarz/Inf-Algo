using JuMP
using GLPK

function read_data(filename)
    num_of_firms = 0
    num_of_airports = 0
    firms_constraints = Int[]
    airports_constraints = Int[]
    costs = Int[]

    open(filename) do io
        num_of_firms = parse(Int, readline(io))
        println(num_of_firms)
        firms_constraints = [parse(Int64, readline(io)) for _ in 1:num_of_firms]
        println(firms_constraints)
        num_of_airports = parse(Int, readline(io))
        println(num_of_airports)
        airports_constraints = [parse(Int64, readline(io)) for _ in 1:num_of_airports]
        costs = [parse(Int64, readline(io)) for _ in 1:num_of_firms*num_of_airports]
    end
    
    return num_of_firms, num_of_airports, firms_constraints, airports_constraints, costs
end

function solve_transportation(num_of_firms, num_of_airports, firms_constraints, airports_constraints, costs)
    lotniska = Model(optimizer_with_attributes(GLPK.Optimizer))

    @variable(lotniska, x[1:num_of_firms, 1:num_of_airports] >= 0)

    @constraint(lotniska, [i=1:num_of_firms], sum(x[i,1:num_of_airports]) <= firms_constraints[i])
    @constraint(lotniska, [i=1:num_of_airports], sum(x[1:num_of_firms,i]) >= airports_constraints[i])

    @objective(lotniska, Min, sum(costs[((i-1)*num_of_airports)+j]*x[i,j] for i in 1:num_of_firms, j in 1:num_of_airports))

    optimize!(lotniska)

    if termination_status(lotniska) == MOI.OPTIMAL
        println("Minimalny koszt: ", objective_value(lotniska))
        for j in 1:num_of_firms
            for i in 1:num_of_airports
                println("x[", j, ",", i, "] = ", value(x[j, i]))
            end
        end
    else
        println("No solution found")
    end
end

filename = "data.txt"
num_of_firms, num_of_airports, firms_constraints, airports_constraints, costs = read_data(filename)
solve_transportation(num_of_firms, num_of_airports, firms_constraints, airports_constraints, costs)