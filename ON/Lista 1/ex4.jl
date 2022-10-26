function weirdInv()
	num = one(Float64)
	while nextfloat(num) * (one(Float64) / nextfloat(num)) == one(Float64) && num < 2
		num = nextfloat(num)
	end

	return nextfloat(num)
end

function minWeirdInv()
	num = nextfloat(zero(Float64))
	while nextfloat(num) * (one(Float64) / nextfloat(num)) == one(Float64)
		num = nextfloat(num)
	end

	return nextfloat(num)
end

println("x: 1 < x < 2; x * (1/x) /= 1; x = $(weirdInv())")
println("x: y * (1/y) /= 1; y = $(minWeirdInv())")