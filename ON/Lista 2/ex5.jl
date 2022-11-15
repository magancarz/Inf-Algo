function population(n, r, p0)
    if (n == 0)
        return p0
    end
    pn1 = population(n - 1, r, p0)
    return pn1 + r * pn1 * (1 - pn1)
end


println("40 iterations Float32: ", population(40, Float32(3), Float32(0.01)))
println("40 iterations Float64: ", population(40, Float32(3), Float64(0.01)))

res = population(10, Float32(3), Float32(0.01))
res = population(10, Float32(3), Float32(trunc(res*1000)/1000))
res = population(10, Float32(3), Float32(trunc(res*1000)/1000))
res = population(10, Float32(3), Float32(trunc(res*1000)/1000))
println("40 iterations with modification (cutting to 3 digits): ", res)