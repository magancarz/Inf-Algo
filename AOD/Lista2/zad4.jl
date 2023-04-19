using JuMP
using GLPK

function solve_cameras_on_grid(n, m, k, containers)
    # utworzenie modelu
    model = Model(GLPK.Optimizer)

    # zmienne decyzyjne
    @variable(model, x[1:n, 1:m], Bin)

    # każdy kontener musi być monitorowany
    for i in 1:n
        for j in 1:m
            if containers[i,j] == 1
                @constraint(model, x[i,j] == 0)
                @constraint(model, sum(x[i,max(j-k,1):min(j+k,m)]) + sum(x[max(i-k,1):min(i+k,n),j]) >= 1)
            end
        end
    end

    # minimalizacja liczby kamer
    @objective(model, Min, sum(x))

    # rozwiązanie problemu
    optimize!(model)

    # wyświetlenie wyniku
    if termination_status(model) == MOI.OPTIMAL
        println("Liczba kamer: ", objective_value(model))
        for i in 1:n
            for j in 1:m
                if value(x[i,j]) > 0.5
                    println("Kamera na pozycji ($i,$j)")
                end
            end
        end
    else
        println("Nie udało się znaleźć optymalnego rozwiązania.")
    end
end


n = 0
m = 0
c = 0


filename = "data.txt"
lines = readlines(filename)
n, m, c = split(lines[1])
n, m, c = parse(Int, n), parse(Int, m), parse(Int, c)
container = zeros(n, m)   

for i in 2:c+1
    from, to = split(lines[i])
    from, to = parse(Int, from), parse(Int, to)
    container[from, to] = 1
end


solve_cameras_on_grid(n,m,3,container)