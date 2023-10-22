import numpy as np
from scipy.optimize import fsolve
import matplotlib.pyplot as plt
import time

# Define the function
def f(x):
    return np.sin(3 * np.pi * np.cos(2 * np.pi * x) * np.sin(np.pi * x))

# Define the range and starting points
a, b = -3, 5
n = 4**9
x0 = np.linspace(a, b, n)

# Find roots using fsolve
roots = []
start_time = time.time()
for x in x0:
    root = fsolve(f, x)[0]
    roots.append(root)
end_time = time.time()

# Keep unique roots
roots = np.unique(roots)

# Plotting the function and its roots
plt.figure(figsize=(12, 3))
xx = np.linspace(a, b, 1001)
plt.plot(xx, f(xx), '-k', linewidth=2)
plt.scatter(roots, f(roots), color='r', s=10)
plt.xlim([a, b])
plt.ylim([-1, 1])
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True)
plt.title(f"Root-finding using Python (Time taken: {end_time - start_time:.4f} seconds)")
plt.savefig("PythonRootFinding.png")
plt.show()
