include("./ex1_2_3.jl")

using .functions1_2_3

function f1(x)
	exp(1 - x) - 1 # 0.8 to 1.5
end

function pf1(x)
	-exp(1 - x)
end

function f2(x)
	x * exp(-x) # -1.0 to 1.5
end

function pf2(x)
	-exp(-x) * (x - 1)
end

delta = 10 ^ (-5)
epsilon = 10 ^ (-5)

println("wyniki dla exp(1 - x) - 1")
println("mbisekcji $(mbisekcji(f1, 0.8, 1.5, delta, epsilon))")
println("mstycznych $(mstycznych(f1, pf1, 0.8, delta, epsilon, 50))")
println("msiecznych $(msiecznych(f1, 0.8, 1.2, delta, epsilon, 50))\n")

println("wyniki dla x * exp(-x)")
println("mbisekcji $(mbisekcji(f2, -0.8, 0.6, delta, epsilon))")
println("mstycznych $(mstycznych(f2, pf2, 1.0, delta, epsilon, 50))")
println("msiecznych $(msiecznych(f2, -0.5, 0.5, delta, epsilon, 50))")