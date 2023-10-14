#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

// Function to calculate the dot product using a loop
double dot_product_loop(const double a[], const double b[]) {
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// Function to calculate the dot product using vectorization
double dot_product_vectorized(const double a[], const double b[]) {
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        result += a[i] * b[i];
    }
    return result;
}

int main() {
    double a[N];
    double b[N];

    // Initialize the vectors with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        a[i] = (double)rand() / RAND_MAX;
        b[i] = (double)rand() / RAND_MAX;
    }

    // Measure time for the loop-based method
    clock_t start = clock();
    double result_loop = dot_product_loop(a, b);
    clock_t end = clock();
    double time_loop = (double)(end - start) / CLOCKS_PER_SEC;

    // Measure time for the vectorized method
    start = clock();
    double result_vectorized = dot_product_vectorized(a, b);
    end = clock();
    double time_vectorized = (double)(end - start) / CLOCKS_PER_SEC;

    // Compare results and calculate speedup
    double speedup = time_loop / time_vectorized;

    // Print results
    printf("Dot product using loop: %f\n", result_loop);
    printf("Dot product using vectorization: %f\n", result_vectorized);
    printf("Results are equal: %s\n", result_loop == result_vectorized ? "Yes" : "No");
    printf("Time for for loop: %f seconds\n", time_loop);
    printf("Time for vectorization: %f seconds\n", time_vectorized);
    printf("Speedup: %f\n", speedup);

    return 0;
}
