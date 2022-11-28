include("./ex1_2_3.jl")

using .functions1_2_3

function f(x)
	return sin(x) - ((1/2) * x) ^ 2
end

function pf(x)
	return cos(x) - (1/2) * x
end

delta = (1/2) * 10 ^ (-5)
epsilon = (1/2) * 10 ^ (-5)

println("wyniki dla sin(x) - ((1/2) * x) ^ 2")
println("mbisekcji $(mbisekcji(f, 1.5, 2.0, delta, epsilon))")
println("mstycznych $(mstycznych(f, pf, 1.5, delta, epsilon, 50))")
println("msiecznych $(msiecznych(f, 1.0, 2.0, delta, epsilon, 50))")