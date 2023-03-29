using JuMP, GLPK

# Inicjalizacja modelu
model = Model(GLPK.Optimizer)

# Dane
dostawcy = 1:3
lotniska = 1:4

dostepne_paliwo = [275000, 550000, 660000]
wymagane_paliwo = [110000, 220000, 330000, 440000]

koszty = [
    10 7 8
    10 11 14
    9 12 4
    11 13 9
]

# Zmienne decyzyjne
@variable(model, ilosc[dostawcy, lotniska] >= 0, Int)

# Funkcja celu
@objective(model, Min, sum(ilosc[d,l] * koszty[l,d] for d in dostawcy, l in lotniska))

# Ograniczenia
for l in lotniska
    @constraint(model, sum(ilosc[d,l] for d in dostawcy) == wymagane_paliwo[l])
end

for d in dostawcy
    @constraint(model, sum(ilosc[d,l] for l in lotniska) <= dostepne_paliwo[d])
end

# Rozwiązanie
optimize!(model)

# Wynik
println("Minimalny koszt: ", objective_value(model))
for d in dostawcy
    if sum(value.(ilosc[d,:])) > 0
        println("Firma ", d, " dostarcza paliwo")
    end
end
for d in dostawcy
    if sum(value.(ilosc[d,:])) < dostepne_paliwo[d]
        println("Możliwość dostawy paliwa przez firmę ", d, " nie została wyczerpana")
    end
end

# Wyświetlenie planu zakupu i dostaw paliwa
println("Plan zakupu i dostaw paliwa na lotniska:")
for l in lotniska
    for d in dostawcy
        ilosc_paliwa = value(ilosc[d,l])
        if ilosc_paliwa > 0
            println("Firma ", d, " dostarcza ", ilosc_paliwa, " galonów paliwa na lotnisko ", l)
        end
    end
end
