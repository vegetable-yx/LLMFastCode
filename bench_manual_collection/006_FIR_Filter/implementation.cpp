#include <immintrin.h>
#include "common.h"

// Precondition: n = 1024, m = 4
void slow_performance(double *__restrict x, double *__restrict y, double *__restrict h, int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        double sum = 0.0;
        for (int k = 0; k < m; ++k)
        {
            int x_index = i + (m - 1) - k;
            sum += (i + k + 1) * h[k] * std::abs(x[x_index]);
        }
        y[i] = sum;
    }
}

void maxperformance(double *__restrict x, double *__restrict y, double *__restrict h, int n, int m)
{
    // Precompute the constant parts of the coefficient: (i + k + 1)
    __m256d h0 = _mm256_set1_pd(h[0]);
    __m256d h1 = _mm256_set1_pd(h[1]);
    __m256d h2 = _mm256_set1_pd(h[2]);
    __m256d h3 = _mm256_set1_pd(h[3]);

    // Process 4 output elements at a time
    int i = 0;
    for (; i <= n - 4; i += 4)
    {
        // Load coefficients for each iteration
        __m256d base_i = _mm256_set_pd(i + 3, i + 2, i + 1, i);

        // For k=0: coefficient = i + 0 + 1 = i + 1
        __m256d coef0 = _mm256_add_pd(base_i, _mm256_set1_pd(1.0));
        // x indices for k=0: i + (4-1) - 0 = i + 3
        __m256d x0 = _mm256_set_pd(
            std::abs(x[i + 3 + 3]),
            std::abs(x[i + 2 + 3]),
            std::abs(x[i + 1 + 3]),
            std::abs(x[i + 0 + 3]));
        __m256d term0 = _mm256_mul_pd(_mm256_mul_pd(coef0, h0), x0);

        // For k=1: coefficient = i + 1 + 1 = i + 2
        __m256d coef1 = _mm256_add_pd(base_i, _mm256_set1_pd(2.0));
        // x indices for k=1: i + (4-1) - 1 = i + 2
        __m256d x1 = _mm256_set_pd(
            std::abs(x[i + 3 + 2]),
            std::abs(x[i + 2 + 2]),
            std::abs(x[i + 1 + 2]),
            std::abs(x[i + 0 + 2]));
        __m256d term1 = _mm256_mul_pd(_mm256_mul_pd(coef1, h1), x1);

        // For k=2: coefficient = i + 2 + 1 = i + 3
        __m256d coef2 = _mm256_add_pd(base_i, _mm256_set1_pd(3.0));
        // x indices for k=2: i + (4-1) - 2 = i + 1
        __m256d x2 = _mm256_set_pd(
            std::abs(x[i + 3 + 1]),
            std::abs(x[i + 2 + 1]),
            std::abs(x[i + 1 + 1]),
            std::abs(x[i + 0 + 1]));
        __m256d term2 = _mm256_mul_pd(_mm256_mul_pd(coef2, h2), x2);

        // For k=3: coefficient = i + 3 + 1 = i + 4
        __m256d coef3 = _mm256_add_pd(base_i, _mm256_set1_pd(4.0));
        // x indices for k=3: i + (4-1) - 3 = i + 0
        __m256d x3 = _mm256_set_pd(
            std::abs(x[i + 3 + 0]),
            std::abs(x[i + 2 + 0]),
            std::abs(x[i + 1 + 0]),
            std::abs(x[i + 0 + 0]));
        __m256d term3 = _mm256_mul_pd(_mm256_mul_pd(coef3, h3), x3);

        // Sum all terms
        __m256d sum = _mm256_add_pd(
            _mm256_add_pd(term0, term1),
            _mm256_add_pd(term2, term3));

        // Store the result
        _mm256_storeu_pd(&y[i], sum);
    }

    // Handle remaining elements
    for (; i < n; ++i)
    {
        double sum = 0.0;
        for (int k = 0; k < m; ++k)
        {
            int x_index = i + (m - 1) - k;
            sum += (i + k + 1) * h[k] * std::abs(x[x_index]);
        }
        y[i] = sum;
    }
}

/*
 * Called by the driver to register your functions
 * Use add_function(func, description) to add your own functions
 */
void register_functions()
{
    add_function(&slow_performance, "slow_performance");
    add_function(&maxperformance, "maxperformance");
}