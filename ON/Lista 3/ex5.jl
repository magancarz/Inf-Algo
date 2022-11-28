include("./ex1_2_3.jl")

using .functions1_2_3

function f(x)
	exp(x) - 3 * x
end

delta = 10 ^ (-4)
epsilon = 10 ^ (-4)

println("wyniki dla exp(x) - 3x")
println("mbisekcji od -3.0 do 1.0 $(mbisekcji(f, 1.0, -3.0, delta, epsilon))")
println("mbisekcji od 1.0 do 3.0 $(mbisekcji(f, 1.0, 3.0, delta, epsilon))")