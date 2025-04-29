#include <immintrin.h>
#include "common.h"

void slow_performance(double *x, double *y, double *z)
{
    for (int i = 0; i < 32; ++i) {
        z[i] = 0.0;
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double real = 0.0;
            double imag = 0.0;
            for (int k = 0; k < 4; ++k) {
                double a = x[(i * 4 + k) * 2];
                double b = x[(i * 4 + k) * 2 + 1];

                double c = y[(k * 4 + j) * 2];
                double d = y[(k * 4 + j) * 2 + 1];

                double prod_real = 2.0 * a * c - b * d;
                double prod_imag = 2.0 * b * c + 2.0 * a * d;

                real += prod_real;
                imag += prod_imag;
            }

            z[(i * 4 + j) * 2] = real;
            z[(i * 4 + j) * 2 + 1] = imag;
        }
    }
}

void maxperformance(double *x, double *y, double *z)
{
    #include <immintrin.h>
    
    // Zero out z array with SIMD
    for (int i = 0; i < 32; i += 4) {
        _mm256_storeu_pd(&z[i], _mm256_setzero_pd());
    }

    // Precompute some offsets to avoid repeated calculations
    const int stride_i = 8;  // i * 4 * 2
    const int stride_k = 2;  // k * 2
    const int stride_j = 8;  // j * 4 * 2
    
    for (int i = 0; i < 4; ++i) {
        int i_offset = i * stride_i;
        
        for (int j = 0; j < 4; ++j) {
            // Initialize accumulators for the dot product
            __m256d acc_real = _mm256_setzero_pd();
            __m256d acc_imag = _mm256_setzero_pd();
            
            // Process all k values at once using AVX
            __m256d a = _mm256_set_pd(
                x[i_offset + 3 * stride_k],
                x[i_offset + 2 * stride_k],
                x[i_offset + 1 * stride_k],
                x[i_offset + 0 * stride_k]
            );
            
            __m256d b = _mm256_set_pd(
                x[i_offset + 3 * stride_k + 1],
                x[i_offset + 2 * stride_k + 1],
                x[i_offset + 1 * stride_k + 1],
                x[i_offset + 0 * stride_k + 1]
            );
            
            for (int k = 0; k < 4; ++k) {
                int k_offset = k * stride_j + j * 2;
                
                // Load y values
                double c = y[k_offset];
                double d = y[k_offset + 1];
                
                // Broadcast c and d to all lanes
                __m256d c_vec = _mm256_set1_pd(c);
                __m256d d_vec = _mm256_set1_pd(d);
                
                // Algebraic optimization: (2.0 * a * c - b * d) and (2.0 * b * c + 2.0 * a * d)
                // Factoring out the 2.0 multiplication where possible
                __m256d two = _mm256_set1_pd(2.0);
                __m256d ac = _mm256_mul_pd(a, c_vec);
                __m256d bd = _mm256_mul_pd(b, d_vec);
                __m256d bc = _mm256_mul_pd(b, c_vec);
                __m256d ad = _mm256_mul_pd(a, d_vec);
                
                // Compute real part: 2.0 * a * c - b * d
                __m256d real_part = _mm256_mul_pd(ac, two);
                real_part = _mm256_sub_pd(real_part, bd);
                
                // Compute imaginary part: 2.0 * b * c + 2.0 * a * d
                __m256d imag_part = _mm256_mul_pd(bc, two);
                __m256d ad_scaled = _mm256_mul_pd(ad, two);
                imag_part = _mm256_add_pd(imag_part, ad_scaled);
                
                // Accumulate results
                acc_real = _mm256_add_pd(acc_real, real_part);
                acc_imag = _mm256_add_pd(acc_imag, imag_part);
            }
            
            // Extract the horizontal sum of the vector
            double real_sum = 0.0;
            double imag_sum = 0.0;
            
            double real_arr[4], imag_arr[4];
            _mm256_storeu_pd(real_arr, acc_real);
            _mm256_storeu_pd(imag_arr, acc_imag);
            
            for (int k = 0; k < 4; ++k) {
                real_sum += real_arr[k];
                imag_sum += imag_arr[k];
            }
            
            // Store the result
            z[(i * 4 + j) * 2] = real_sum;
            z[(i * 4 + j) * 2 + 1] = imag_sum;
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