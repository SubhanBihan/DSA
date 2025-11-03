import math

n = 1000

galton_n = [math.comb(n, k) / (2 ** n) for k in range(n + 1)]

# print("Galton's distribution for n =", n)
# print(*galton_n, sep=", ")

start = 400
end = 600
print("Percentage of Galton's distribution between", start, "and", end, ": ", sum(galton_n[start:end+1]) * 100, "%")