module functions1_2_3

	export mbisekcji, mstycznych, msiecznych

	function mbisekcji(f, a::Float64, b::Float64, delta::Float64, epsilon::Float64)
		y1 = f(a)
		y2 = f(b)
		diff = b - a

		if(sign(y1) == sign(y2))
			return (0, 0, 0, 1)
		end

		i = 0
		while true
			i = i + 1
			diff = diff / 2
			m = a + diff
			r = f(m)

			if(abs(diff) < delta || abs(r) < epsilon)
				return (m, r, i, 0)
			end

			if(sign(r) != sign(y1))
				b = m
				y2 = r
			else
				a = m
				y1 = r
			end
		end
	end

	function mstycznych(f, pf, x0::Float64, delta::Float64, epsilon::Float64, maxit::Int)
		r = f(x0)

		if(abs(r) < epsilon)
			return (x0, r, 0, 0)
		end

		if(abs(pf(x0)) < epsilon)
			return (0, 0, 0, 2)
		end

		i = 0
		while (i <= maxit)
			i = i + 1
			x1 = x0 - r / pf(x0)
			r = f(x1)
			if(abs(x1 - x0) < delta || abs(r) < epsilon)
				return (x1, r, i, 0)
			end
			x0 = x1
		end
		return (0, 0, 0, 1)
	end

	function msiecznych(f, x0::Float64, x1::Float64, delta::Float64, epsilon::Float64, maxit::Int)
		y1 = f(x0)
		y2 = f(x1)

		i = 0
		while (i <= maxit)
			i = i +1

			if(abs(y1) > abs(y2))
				x0, x1 = x1, x0
				y1, y2 = y2, y1
			end

			v = (x1 - x0)/(y2 - y1)
			x1 = x0
			y2 = y1
			x0 = x0 - (y2 * v)
			y1 = f(x0)
			if(abs(x1 - x0) < delta || abs(y1) < epsilon)
				return (x0, y1, i, 0)
			end
		end
		return (0, 0, 0, 1)
	end
end