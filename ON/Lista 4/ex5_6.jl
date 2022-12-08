include("./ex1_2_3_4.jl")
using .ex1_2_3_4

function e(x)
	return exp(x)
end

function x2sinx(x)
	return x^2 * sin(x)
end

rysujNnfx(e, 0.0, 1.0, 5)
rysujNnfx(e, 0.0, 1.0, 10)
rysujNnfx(e, 0.0, 1.0, 15)

rysujNnfx(x2sinx, -1.0, 1.0, 5)
rysujNnfx(x2sinx, -1.0, 1.0, 10)
rysujNnfx(x2sinx, -1.0, 1.0, 15)

function absx(x)
	return abs(x)
end

function ex6frac(x)
	return 1 / (1 + x^2)
end

rysujNnfx(absx, -1.0, 1.0, 5)
rysujNnfx(absx, -1.0, 1.0, 10)
rysujNnfx(absx, -1.0, 1.0, 15)

rysujNnfx(ex6frac, -5.0, 5.0, 5)
rysujNnfx(ex6frac, -5.0, 5.0, 10)
rysujNnfx(ex6frac, -5.0, 5.0, 15)