
import sys
import numpy as np
from scipy.optimize import linprog

# Read input
lines = sys.stdin.readlines()
p, q = map(int, lines[0].split())

A = []
for i in range(1, p + 1):
    row = list(map(float, lines[i].split()))
    A.append(row)
A = np.array(A)

b = np.array(list(map(float, lines[p + 1].split())))
c = np.array(list(map(float, lines[p + 2].split())))

# Solve: maximize c'x subject to Ax <= b, x >= 0
# linprog minimizes, so we use -c
result = linprog(-c, A_ub=A, b_ub=b, bounds=(0, None), method='highs')

if result.status == 0:  # Optimal
    print("Bounded solution")
    print(' '.join(f"{x:.15f}" for x in result.x))
elif result.status == 3:  # Unbounded
    print("Infinity")
else:  # Infeasible or other error
    print("No solution")