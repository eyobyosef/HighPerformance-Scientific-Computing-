#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

void random_fill(double matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (double) rand() / RAND_MAX;
        }
    }
}

void nested_loops_multiply(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void loop_vectorized_multiply(double A[N][N], double B[N][N], double CC[N][N]) {
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            CC[i][j] = 0;
            for (int k = 0; k < N; k++) {
                CC[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void print_time_taken(clock_t start, const char* method) {
    clock_t end = clock();
    double time_taken = ((double) end - start) / CLOCKS_PER_SEC;
    printf("Time taken by %s: %f seconds\n", method, time_taken);
}

int main() {
    double A[N][N], B[N][N], C[N][N], CC[N][N], CCC[N][N];

    // Initialize matrices A and B with random values
    random_fill(A);
    random_fill(B);

    // Time nested loops method
    clock_t start_time = clock();
    nested_loops_multiply(A, B, C);
    print_time_taken(start_time, "nested loops method");

    // Time loop vectorized method
    start_time = clock();
    loop_vectorized_multiply(A, B, CC);
    print_time_taken(start_time, "loop with vectorization method");

    // Since C doesn't have a built-in direct matrix multiplication function,
    // we'll reuse the nested loops method for direct multiplication
    start_time = clock();
    nested_loops_multiply(A, B, CCC);
    print_time_taken(start_time, "direct multiplication method");

    return 0;
}
