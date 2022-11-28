include("./ex1_2_3.jl")

using .functions1_2_3

delta = (1/2)*10^(-5)
epsilon = (1/2)*10^(-5)

function ftest(x)
	return x^2 - 2
end

function fprimtest(x)
	return 2 * x
end

println("wyniki dla x^2 - 2")
println("mbisekcji $(mbisekcji(ftest, 0.0, 2.0, delta, epsilon))")
println("mstycznych $(mstycznych(ftest, fprimtest, 2.0, delta, epsilon, 50))")
println("msiecznych $(msiecznych(ftest, 0.0, 2.0, delta, epsilon, 50))")