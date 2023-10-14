import time
import multiprocessing

# Define the time-consuming function
def timeconsumingfun(_):
    time.sleep(5)  # Simulate a time-consuming task (5 seconds)

# Create a parallel computing class
class ParallelExperiment:
    def __init__(self):
        self.pool = multiprocessing.Pool()
    
    def run(self, n):
        start_time = time.time()
        
        # Use starmap to pass arguments to timeconsumingfun
        self.pool.starmap(timeconsumingfun, [(None,) for _ in range(n)])
        
        end_time = time.time()
        
        # Calculate the time taken for parallel execution
        self.parallel_time = end_time - start_time
        
        # Calculate speedup
        self.speedup = n * 5 / self.parallel_time
        
        # Calculate efficiency
        self.efficiency = self.speedup / multiprocessing.cpu_count()

# Experiment for different values of n
n_values = [4, 8, 16]  # Small, medium, and large values of n

for n in n_values:
    experiment = ParallelExperiment()
    experiment.run(n)
    
    print(f"Experiment with n = {n}:")
    print(f"Parallel Execution Time: {experiment.parallel_time} seconds")
    print(f"Speedup: {experiment.speedup:.2f}")
    print(f"Efficiency: {experiment.efficiency:.2%}")
    print()
