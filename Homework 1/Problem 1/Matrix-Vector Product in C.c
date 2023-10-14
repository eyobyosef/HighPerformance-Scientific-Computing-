#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MATRIX_SIZE 100

// Function to initialize a random matrix of size NxN
void initializeMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

// Function to calculate the matrix product using nested loops
void matrixMultiplicationNestedLoops(double A[MATRIX_SIZE][MATRIX_SIZE], double B[MATRIX_SIZE][MATRIX_SIZE], double C[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL));

    double matrixA[MATRIX_SIZE][MATRIX_SIZE];
    double matrixB[MATRIX_SIZE][MATRIX_SIZE];
    double matrixC[MATRIX_SIZE][MATRIX_SIZE];
    double matrixCC[MATRIX_SIZE][MATRIX_SIZE];
    double matrixCCC[MATRIX_SIZE][MATRIX_SIZE];

    // Matrix Initialization
    initializeMatrix(matrixA);
    initializeMatrix(matrixB);

    // Matrix Multiplication Using Nested Loops
    clock_t start = clock();
    matrixMultiplicationNestedLoops(matrixA, matrixB, matrixC);
    clock_t end = clock();
    double timeNestedLoops = (double)(end - start) / CLOCKS_PER_SEC;

    // Matrix Multiplication Using Vectorization (direct loop)
    start = clock();
    matrixMultiplicationNestedLoops(matrixA, matrixB, matrixCC);
    end = clock();
    double timeVectorization = (double)(end - start) / CLOCKS_PER_SEC;

    // Matrix Multiplication Using Matrix Operation (direct multiplication)
    start = clock();
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrixCCC[i][j] = 0.0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                matrixCCC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    end = clock();
    double timeMatrixOperation = (double)(end - start) / CLOCKS_PER_SEC;

    // Timing Measurements

    // Norm Calculation
    double normCC = 0.0;
    double normCCC = 0.0;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            normCC += (matrixC[i][j] - matrixCC[i][j]) * (matrixC[i][j] - matrixCC[i][j]);
            normCCC += (matrixC[i][j] - matrixCCC[i][j]) * (matrixC[i][j] - matrixCCC[i][j]);
        }
    }

    normCC = sqrt(normCC);
    normCCC = sqrt(normCCC);

    // Speedup Calculations
    double speedupNestedLoopsToVectorization = timeNestedLoops / timeVectorization;
    double speedupNestedLoopsToMatrixOperation = timeNestedLoops / timeMatrixOperation;
    double speedupVectorizationToMatrixOperation = timeVectorization / timeMatrixOperation;

    // Output
    printf("Matrix Multiplication Using Nested Loops: %f\n", timeNestedLoops);
    printf("Matrix Multiplication Using Matrix Operation: %f\n", timeMatrixOperation);
    printf("Matrix Multiplication Using Vectorization: %f\n", timeVectorization);
    printf("Speedup (Nested Loops vs. Matrix Operation): %f\n", speedupNestedLoopsToMatrixOperation);
    printf("Speedup (Nested Loops vs. Vectorization): %f\n", speedupNestedLoopsToVectorization);
    printf("Norm (C - CC): %f\n", normCC);
    printf("Norm (C - CCC): %f\n", normCCC);

    return 0;
}
