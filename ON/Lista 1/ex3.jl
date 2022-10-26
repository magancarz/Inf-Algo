function test(first::Float64, last::Float64, step::Float64)
	last = prevfloat(last)
	firstExp = SubString(bitstring(first), 2:12)
	lastExp = SubString(bitstring(last), 2:12)
	if(firstExp != lastExp)
		return false
	end

	if(((2.0 ^ (parse(Int, firstExp, base = 2) - 1023)) * 2.0 ^ (-52)) != step)
		return false
	end

	return true
end

println(test(1.0, 2.0, 2^(-52)))

function numberSpreadTest(first::Float64, last::Float64)
	last = prevfloat(last)
	firstExp = SubString(bitstring(first), 2:12)
	lastExp = SubString(bitstring(last), 2:12)
	if(firstExp != lastExp)
		return 0.0
	end

	return ((2.0 ^ (parse(Int, firstExp, base = 2) - 1023)) * 2.0 ^ (-52))
end

println(numberSpreadTest(0.5, 1.0))
println(numberSpreadTest(2.0, 4.0))