#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Define the number of threads
#define NUM_THREADS 4

// Define the time-consuming function
void *timeconsumingfun(void *arg) {
    usleep(5000000);  // Simulate a time-consuming task (5 seconds)
    pthread_exit(NULL);
}

int main() {
    int n_values[] = {4, 8, 16};  // Small, medium, and large values of n
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    clock_t start, end;

    for (int n_index = 0; n_index < 3; n_index++) {
        int n = n_values[n_index];

        start = clock();

        for (t = 0; t < NUM_THREADS; t++) {
            rc = pthread_create(&threads[t], NULL, timeconsumingfun, (void *)t);
            if (rc) {
                printf("Error creating thread %ld\n", t);
                exit(-1);
            }
        }

        for (t = 0; t < NUM_THREADS; t++) {
            pthread_join(threads[t], NULL);
        }

        end = clock();

        double parallel_time = (double)(end - start) / CLOCKS_PER_SEC;
        double speedup = n * 5 / parallel_time;
        double efficiency = speedup / NUM_THREADS;

        printf("Experiment with n = %d:\n", n);
        printf("Parallel Execution Time: %.2f seconds\n", parallel_time);
        printf("Speedup: %.2f\n", speedup);
        printf("Efficiency: %.2f%%\n\n");
    }

    pthread_exit(NULL);
}
