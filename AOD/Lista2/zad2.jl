using JuMP, GLPK

# data
n = 5  # number of cities
m = 6  # number of connections
T = 20  # maximum travel time
c = [ 0.0 1.0 0.0 2.0 0.0;
      0.0 0.0 1.0 5.0 0.0;
      0.0 0.0 0.0 0.0 0.0;
      0.0 0.0 0.0 0.0 3.0;
      0.0 0.0 5.0 0.0 0.0]  # connection costs
t = [ T+1 10.0 T+1 2.0 T+1;
      T+1 T+1 11.0 8.0 T+1;
      T+1 T+1 T+1 T+1 T+1;
      T+1 T+1 T+1 T+1 4.0;
      T+1 T+1 8.0 T+1 T+1]  # connection times
i_star = 1  # starting city
j_star = 3  # ending city

# create model
model = Model(GLPK.Optimizer)

# variables
@variable(model, x[1:n, 1:n], Bin)  # x[i,j] = 1 if connection (i,j) is used
@variable(model, total_cost >= 0)  # total cost of the path
@variable(model, total_time >= 0)  # total time of the path

# objective
@objective(model, Min, total_cost)

# constraints
@constraint(model, total_time == sum(t[i,j] * x[i,j] for i in 1:n, j in 1:n))
@constraint(model, sum(x[i_star,j] for j in 1:n) == sum(x[i,j_star] for i in 1:n))

@constraint(model, sum(x[i,j_star] for i in 1:n) == 1)  # end at j_star
for i in 1:n
    for j in 1:n
        @constraint(model, total_cost >= c[i,j] * x[i,j])  # enforce x[i,j] = 1 => use cost c[i,j]
    end
end
@constraint(model, total_time <= T)  # limit total time

# solve and print results
optimize!(model)
println("Total cost: ", objective_value(model))
println("Total time: ", value(total_time))
println("Path: ")
for i in 1:n
    for j in 1:n
        if value(x[i,j]) > 0
            println(i, " -> ", j)
        end
    end
end