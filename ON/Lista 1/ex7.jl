function derivative(f, x, h)
	(f(x + h) - f(x)) / h
end

function f(x)
	sin(x) + cos(3.0 * x)
end

function fPrim(x)
	cos(x) - 3.0 * sin(3.0 * x)
end

res = fPrim(1.0)

for i in 1:54
	fTilde = derivative(f, 1.0, 2.0 ^ -i)
	println("2^-$i
       f_tilde = $(fTilde)
|f_tilde - f'| = $(abs(fTilde - res))\n")
end