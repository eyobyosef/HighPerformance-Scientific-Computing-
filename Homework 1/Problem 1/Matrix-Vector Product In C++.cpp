#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

const int N = 100; // Size of the square matrix and vector

// Function to calculate the dot product using nested loops
std::vector<double> dot_product_nested_loops(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    int n = A.size();
    std::vector<double> b(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i] += A[i][j] * x[j];
        }
    }

    return b;
}

// Function to calculate the dot product using vectorization
std::vector<double> dot_product_vectorized(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    int n = A.size();
    std::vector<double> b(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i] += A[i][j] * x[j];
        }
    }

    return b;
}

int main() {
    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    std::vector<double> x(N);

    // Initialize vectors with random values
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < N; i++) {
        x[i] = distribution(generator);
        for (int j = 0; j < N; j++) {
            A[i][j] = distribution(generator);
        }
    }

    // Measure time for the nested loops method
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> b = dot_product_nested_loops(A, x);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_nested_loops = end - start;

    // Measure time for the vectorized method
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> bb = dot_product_vectorized(A, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_vectorized = end - start;

    // Calculate the matrix-vector product using matrix operation
    std::vector<double> bbb(N);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        bbb[i] = 0.0;
        for (int j = 0; j < N; j++) {
            bbb[i] += A[i][j] * x[j];
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_matrix_operation = end - start;

    // Compare results and calculate speedup
    bool results_equal = (b == bb) && (bb == bbb);
    double speedup_nested_loops = time_nested_loops.count() / time_matrix_operation.count();
    double speedup_vectorization = time_nested_loops.count() / time_vectorized.count();

    // Calculate the norms
    double norm_bb = 0.0;
    for (int i = 0; i < N; i++) {
        norm_bb += std::pow(b[i] - bb[i], 2);
    }
    norm_bb = std::sqrt(norm_bb);

    double norm_bbb = 0.0;
    for (int i = 0; i < N; i++) {
        norm_bbb += std::pow(b[i] - bbb[i], 2);
    }
    norm_bbb = std::sqrt(norm_bbb);

    double additional_speedup = time_nested_loops.count() / time_matrix_operation.count();

    // Print results
    std::cout << "Matrix-Vector Multiplication Using Nested Loops: " << results_equal << std::endl;
    std::cout << "Matrix-Vector Multiplication Using Matrix Operation: " << results_equal << std::endl;
    std::cout << "Matrix-Vector Multiplication Using Vectorization: " << results_equal << std::endl;
    std::cout << "Speedup (Nested Loops vs. Matrix Operation): " << speedup_nested_loops << std::endl;
    std::cout << "Speedup (Nested Loops vs. Vectorization): " << speedup_vectorization << std::endl;
    std::cout << "Norm (b - bb): " << norm_bb << std::endl;
    std::cout << "Norm (b - bbb): " << norm_bbb << std::endl;
    std::cout << "Additional Speedup (Nested Loops vs. Matrix Operation): " << additional_speedup << std::endl;

    return 0;
}
