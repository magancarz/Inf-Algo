function values(reps, c, x0)
    values = [x0]
    for i in 1:reps - 1
        append!(values, values[i]^2 + c)
    end
    return values
end

variations = [
    (-2, 1),
    (-2, 2),
    (-2, 1.99999999999999),
    (-1, 1),
    (-1, -1),
    (-1, 0.75),
    (-1, 0.25)
]

reps = 40
foreach(x -> println(x, ":\n\t", join(values(reps, x[1], x[2]), ",")), variations)