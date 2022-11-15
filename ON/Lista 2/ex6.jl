function values(reps, c, x0)
    values = [x0]
    for i in 1:reps-1
        append!(values, values[i]^2+c)
    end
    return values
end

ans = [
	values(40, -2, 1),
	values(40, -2, 2),
	values(40, -2, 1.99999999999999),
	values(40, -1, 1),
	values(40, -1, -1),
	values(40, -1, 0.75),
	values(40, -1, 0.25),
]

for i in 1:40
	println("$(ans[1][i]) & $(ans[2][i]) & $(ans[3][i]) & $(ans[4][i]) & $(ans[5][i]) & $(ans[6][i]) & $(ans[7][i])\\\\ \n \\hline")
end