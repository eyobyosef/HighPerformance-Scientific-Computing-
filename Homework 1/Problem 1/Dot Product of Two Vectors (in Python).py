import numpy as np
import time

# Generate two random column vectors with 10,000 elements
n = 10000  # Correct the variable name to 'n'
x = np.random.rand(n, 1)
y = np.random.rand(n, 1)

# Method 1: Dot product with a for loop
start_time = time.time()
l = 0
for i in range(n):
    l += x[i] * y[i]  # Correct variable names 'a' to 'x' and 'b' to 'y'
time_for_loop = time.time() - start_time

# Method 2: Dot product with vectorization
start_time = time.time()
j = np.dot(x.T, y)
vec_time = time.time() - start_time

# Check if the results are equal
final_result = np.allclose(l, j)

# Calculate the speedup
speedup = time_for_loop / vec_time  # Correct variable name 'time_vectorization' to 'vec_time'

# Print the results
print("Dot product with for loop: ", l)
print("Dot product with vectorization: ", j)
print("Results are equal: ", final_result)
print("Time for for loop: ", time_for_loop)
print("Time for vectorization: ", vec_time)
print("Speedup: ", speedup)
