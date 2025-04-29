#include <immintrin.h>
#include <math.h>
#include "common.h"

// Precondition : 0 <= y[i] < 1.0, n = 1024
void slow_performance(double *x, double *y, int n) {
    for (int i = 0; i < n; i++) {
        unsigned int k = floor(4.0 * y[i]);

        double real = x[2 * i];
        double imag = x[2 * i + 1];

        double real_sqr = real * real - imag * imag;
        double imag_sqr = 2.0 * real * imag;

        switch (k) {
            case 0:
                y[i] += fmin(real_sqr, imag_sqr);
                break;
            case 1:
                y[i] += fmax(real_sqr, imag_sqr);
                break;
            default:
                y[i] += real * real + imag * imag;
                break;
        }
    }
}

#include <immintrin.h>
#include <math.h>

void maxperformance(double *x, double *y, int n)
{
    // Process 4 elements at a time using AVX2
    int i = 0;
    for (; i <= n - 4; i += 4) {
        // Load y values
        __m256d y_vec = _mm256_loadu_pd(&y[i]);
        
        // Calculate k values: k = floor(4.0 * y[i])
        __m256d y_scaled = _mm256_mul_pd(y_vec, _mm256_set1_pd(4.0));
        __m256d k_double = _mm256_floor_pd(y_scaled);
        
        // Load real and imaginary parts
        __m256d real0 = _mm256_set_pd(x[2*(i+3)], x[2*(i+2)], x[2*(i+1)], x[2*i]);
        __m256d imag0 = _mm256_set_pd(x[2*(i+3)+1], x[2*(i+2)+1], x[2*(i+1)+1], x[2*i+1]);
        
        // Calculate real_sqr = real * real - imag * imag
        __m256d real_sqr = _mm256_sub_pd(_mm256_mul_pd(real0, real0), _mm256_mul_pd(imag0, imag0));
        
        // Calculate imag_sqr = 2.0 * real * imag
        __m256d imag_sqr = _mm256_mul_pd(_mm256_mul_pd(real0, imag0), _mm256_set1_pd(2.0));
        
        // Calculate sum_sqr = real * real + imag * imag for default case
        __m256d sum_sqr = _mm256_add_pd(_mm256_mul_pd(real0, real0), _mm256_mul_pd(imag0, imag0));
        
        // Calculate min(real_sqr, imag_sqr) for case 0
        __m256d min_val = _mm256_min_pd(real_sqr, imag_sqr);
        
        // Calculate max(real_sqr, imag_sqr) for case 1
        __m256d max_val = _mm256_max_pd(real_sqr, imag_sqr);
        
        // Prepare masks for the different cases
        __m256d mask0 = _mm256_cmp_pd(k_double, _mm256_set1_pd(0), _CMP_EQ_OQ);
        __m256d mask1 = _mm256_cmp_pd(k_double, _mm256_set1_pd(1), _CMP_EQ_OQ);
        
        // Select the appropriate values based on k
        __m256d result = _mm256_set1_pd(0.0);
        
        // Apply case 0 values where k == 0
        result = _mm256_blendv_pd(result, min_val, mask0);
        
        // Apply case 1 values where k == 1
        __m256d temp = _mm256_blendv_pd(_mm256_set1_pd(0.0), max_val, mask1);
        result = _mm256_add_pd(result, temp);
        
        // Apply default case (k >= 2) values where neither mask0 nor mask1 is set
        __m256d default_mask = _mm256_and_pd(_mm256_cmp_pd(mask0, _mm256_set1_pd(0), _CMP_EQ_OQ), 
                                           _mm256_cmp_pd(mask1, _mm256_set1_pd(0), _CMP_EQ_OQ));
        temp = _mm256_blendv_pd(_mm256_set1_pd(0.0), sum_sqr, default_mask);
        result = _mm256_add_pd(result, temp);
        
        // Add the result to y
        y_vec = _mm256_add_pd(y_vec, result);
        
        // Store the updated y values
        _mm256_storeu_pd(&y[i], y_vec);
    }
    
    // Handle remaining elements
    for (; i < n; i++) {
        unsigned int k = (unsigned int)floor(4.0 * y[i]);
        
        double real = x[2 * i];
        double imag = x[2 * i + 1];
        
        double real_sqr = real * real - imag * imag;
        double imag_sqr = 2.0 * real * imag;
        
        switch (k) {
            case 0:
                y[i] += (real_sqr < imag_sqr) ? real_sqr : imag_sqr;
                break;
            case 1:
                y[i] += (real_sqr > imag_sqr) ? real_sqr : imag_sqr;
                break;
            default:
                y[i] += real * real + imag * imag;
                break;
        }
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