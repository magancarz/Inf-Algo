function kahanMacheps(type)
	num = one(type)
	return 3 * num * ((4 * num) / (3 * num) - num) - num
end

println("Float 16:
kahanMacheps: $(kahanMacheps(Float16))
         eps: $(eps(Float16))\n")

println("Float 32:
kahanMacheps: $(kahanMacheps(Float32))
         eps: $(eps(Float32))\n")

println("Float 64:
kahanMacheps: $(kahanMacheps(Float64))
         eps: $(eps(Float64))\n")