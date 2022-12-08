include("./ex1_2_3_4.jl")
using .ex1_2_3_4

# x^2 - 2
xs = [1.0, 3.0, 4.0, 5.0]
fxs = [-1.0, 7.0, 14.0, 23.0]

expectedQs = [-1.0, 4.0, 1.0, 0.0]
calculatedQs = ilorazyRoznicowe(xs, fxs)

println("xs: $(xs)")
println("fxs: $(fxs)")

println("Test ilorazyRoznicowe(xs, fxs):
wynik: $(calculatedQs)
spodziewane wyniki: $(expectedQs)\n")

println("Test warNewton(xs, calculatedQs, 1.0):
wynik: $(warNewton(xs, calculatedQs, 1.0))
spodziewany wynik: $(-1.0)\n")

expectedNaturals = [-242.0, 388.0, -170.0, 23.0]

println("Test naturalna(xs, fxs)
wynik: $(naturalna(xs, fxs))
spodziewany wynik: $(expectedNaturals)")