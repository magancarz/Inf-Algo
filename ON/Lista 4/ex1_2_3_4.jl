module ex1_2_3_4
using PyPlot
	export ilorazyRoznicowe, warNewton, naturalna, rysujNnfx

	function ilorazyRoznicowe(x::Vector{Float64}, f::Vector{Float64})
		xlength = length(x)
		fx = ones(xlength)

		for i in 1:xlength
			fx[i] = f[i]
		end

		for i in 1:xlength
			for j in xlength:-1:(i + 1)
				fx[j] = (fx[j] - fx[j - 1]) / (x[j] - x[j - i])
			end
		end

		return fx
	end

	function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
		xlength = length(x)
		nt = fx[xlength]

		for i in (xlength-1):-1:1
			nt = fx[i] + (t - x[i]) * nt
		end

		return nt
	end

	function naturalna(x::Vector{Float64}, fx::Vector{Float64})
		xlength = length(x)
	    a = zeros(xlength)
	    a[xlength] = fx[xlength]

	    for i in (xlength-1):-1:1
	        a[i] = fx[i] - x[i] * a[i+1]
	        for j in (i+1):(xlength-1)
	            a[j] += -x[i] * a[j+1]
	        end
	    end

	    return a
	end

	function rysujNnfx(f, a::Float64, b::Float64, n::Int)
		j = n + 1

		xs = Vector{Float64}(undef, j)
		ys = Vector{Float64}(undef, j)

		delta = zero(Float64)
		for i in 1:j
			xs[i] = a + delta
			ys[i] = f(xs[i])
			delta += (b - a) / (j - 1)
		end

		j = (n + 1) * 10

		qs = ilorazyRoznicowe(xs, ys)
		intpoXs = Vector{Float64}(undef, j)
		intpoYs = Vector{Float64}(undef, j)
		realYs = Vector{Float64}(undef, j)

		delta = zero(Float64)
		for i in 1:j
			intpoXs[i] = a + delta
			intpoYs[i] = warNewton(xs, qs, a + delta)
			realYs[i] = f(a + delta)
			delta += (b - a) / (j - 1)
		end

		clf()
		plot(intpoXs, intpoYs, label="wielomian interpolacyjny", linewidth=3.0, alpha=0.6, color="#801515")
		plot(intpoXs, realYs, label="funkcja interpolowana", linewidth=3.0, alpha=0.6, color="#116611")
		legend(title=string("wykres dla n = ", n))
		savefig(string("plots/plot", f, "-", n, ".png"))
	end
end