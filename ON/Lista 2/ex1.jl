x = [2.718281828, −3.141592654, 1.414213562, 0.577215664, 0.301029995]
y = [1486.2497, 878366.9879, −22.37492, 4773714.647, 0.000185049]

x32 = map(el -> convert(Float32, el), x)
y32 = map(el -> convert(Float32, el), y)

x64 = map(el -> convert(Float64, el), x)
y64 = map(el -> convert(Float64, el), y)

function a(x, y)
	s = 0.0
	for i in (1:length(x))
		s += x[i] * y[i]
	end

	return s
end

function b(x, y)
	s = 0.0
	for i in reverse(1:length(x))
		s += x[i] * y[i]
	end

	return s
end

function c(x, y)
	p = x .* y
	sumPos = sum(sort(filter(a -> a > 0, p), rev = true))
	sumNeg = sum(sort(filter(a -> a < 0, p)))
	return sumPos + sumNeg
end

function d(x, y)
	p = x .* y
	sumPos = sum(sort(filter(a -> a > 0, p)))
	sumNeg = sum(sort(filter(a -> a < 0, p), rev = true))
	return sumPos + sumNeg
end

println("Float32:
        real: −1.00657107000000e-11
     forward: $(a(x32, y32))
    backward: $(b(x32, y32))
        desc: $(c(x32, y32))
         asc: $(d(x32, y32))")

println("Float64:
        real: −1.00657107000000e-11
     forward: $(a(x64, y64))
    backward: $(b(x64, y64))
        desc: $(c(x64, y64))
         asc: $(d(x64, y64))")