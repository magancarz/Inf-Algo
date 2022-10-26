function f(num)
	sqrt((num ^ 2.0) + 1.0) - 1.0
end

function g(num)
	(num ^ 2.0) / (sqrt((num ^ 2.0) + 1.0) + 1.0)
end

for i in 1:10
	println("8^-$i
f(x) = $(f(8.0^-i))
g(x) = $(g(8.0^-i))")
end