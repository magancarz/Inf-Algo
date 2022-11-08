using Printf

function macheps(type)
	num = one(type)
	while one(type) + num / 2 != one(type)
		num /= 2
	end
	return num
end

function eta(type)
	num = one(type)
	while num / 2 != zero(type)
		num /= 2
	end
	return num
end

function maxnum(type)
	num = one(type)
	while !isinf(num * 2)
		num *= 2
	end

	gap = num / 2
	while !isinf(num + gap) && gap >= one(type)
		num += gap
		gap /= 2
	end
	return num
end

println("Float 16:
  macheps: $(macheps(Float16))
      eps: $(eps(Float16))

      eta: $(eta(Float16))
nextfloat: $(nextfloat(zero(Float16)))
   
   maxnum: $(maxnum(Float16))
 floatmax: $(floatmax(Float16))\n")

println("Float 32:
  macheps: $(macheps(Float32))
      eps: $(eps(Float32))

      eta: $(eta(Float32))
nextfloat: $(nextfloat(zero(Float32)))
   
   maxnum: $(maxnum(Float32))
 floatmax: $(floatmax(Float32))\n")

println("Float 64:
  macheps: $(macheps(Float64))
      eps: $(eps(Float64))

      eta: $(eta(Float64))
nextfloat: $(nextfloat(zero(Float64)))
   
   maxnum: $(maxnum(Float64))
 floatmax: $(floatmax(Float64))\n")

@printf("Float16 myEta: %.3e
 Float16 eta: %.3e\n", eta(Float16), nextfloat(zero(Float16)))
@printf("Float32 myEta: %.3e
 Float32 eta: %.3e\n", eta(Float32), nextfloat(zero(Float32)))
@printf("Float64 myEta: %.3e
 Float64 eta: %.3e\n", eta(Float64), nextfloat(zero(Float64)))