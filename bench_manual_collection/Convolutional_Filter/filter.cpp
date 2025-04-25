#include "common.h"
#include <immintrin.h>
#include <math.h>

#define K 4
#define N 128

#define GET_X(i, j) x[(i) * N + (j)]
#define GET_Y(i, j) y[(i) * ON + (j)]
#define GET_H(i, j) h[(i) * K + (j)]

void slow_performance1(double *x, double *h, double *y)
{
    const int ON = N - K + 1;
    for (int i = 0; i < ON; i++)
    {
        for (int j = 0; j < ON; j++)
        {
            GET_Y(i, j) = 0.0;
            for (int k0 = 0; k0 < K; k0++)
            {
                for (int k1 = 0; k1 < K; k1++)
                {
                    GET_Y(i, j) += (i + j + k0 + k1 - 1) * GET_H(k0, k1) * fabs(GET_X(i + k0, j + k1));
                }
            }
        }
    }
}

void maxperformance(double *x, double *h, double *y)
{
    const int ON = N - K + 1;
    const double kernel_offset[16] = {
        -1.0, 0.0, 1.0, 2.0,
        0.0, 1.0, 2.0, 3.0,
        1.0, 2.0, 3.0, 4.0,
        2.0, 3.0, 4.0, 5.0};

    double kernel[16];
    for (int k0 = 0; k0 < 4; k0++)
    {
        for (int k1 = 0; k1 < 4; k1++)
        {
            kernel[k0 * 4 + k1] = GET_H(k0, k1);
        }
    }

    __m256d abs_mask = _mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFFLL));

    int i;
    for (i = 0; i <= ON - 2; i += 2)
    {
        int j;
        for (j = 0; j <= ON - 4; j += 4)
        {
            __m256d ymm_y0 = _mm256_setzero_pd();
            __m256d ymm_y1 = _mm256_setzero_pd();

            __m256d ymm_j = _mm256_set_pd((double)(j + 3), (double)(j + 2), (double)(j + 1), (double)j);

            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[0]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[0]));
                __m256d h_val = _mm256_set1_pd(kernel[0]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 0, j + 0));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 1, j + 0));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[1]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[1]));
                __m256d h_val = _mm256_set1_pd(kernel[1]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 0, j + 1));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 1, j + 1));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[2]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[2]));
                __m256d h_val = _mm256_set1_pd(kernel[2]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 0, j + 2));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 1, j + 2));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[3]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[3]));
                __m256d h_val = _mm256_set1_pd(kernel[3]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 0, j + 3));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 1, j + 3));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[4]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[4]));
                __m256d h_val = _mm256_set1_pd(kernel[4]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 1, j + 0));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 2, j + 0)); // row i+2 for second output row
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[5]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[5]));
                __m256d h_val = _mm256_set1_pd(kernel[5]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 1, j + 1));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 2, j + 1));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[6]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[6]));
                __m256d h_val = _mm256_set1_pd(kernel[6]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 1, j + 2));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 2, j + 2));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[7]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[7]));
                __m256d h_val = _mm256_set1_pd(kernel[7]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 1, j + 3));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 2, j + 3));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[8]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[8]));
                __m256d h_val = _mm256_set1_pd(kernel[8]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 2, j + 0));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 3, j + 0));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[9]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[9]));
                __m256d h_val = _mm256_set1_pd(kernel[9]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 2, j + 1));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 3, j + 1));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[10]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[10]));
                __m256d h_val = _mm256_set1_pd(kernel[10]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 2, j + 2));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 3, j + 2));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[11]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[11]));
                __m256d h_val = _mm256_set1_pd(kernel[11]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 2, j + 3));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 3, j + 3));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[12]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[12]));
                __m256d h_val = _mm256_set1_pd(kernel[12]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 3, j + 0));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 4, j + 0));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[13]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[13]));
                __m256d h_val = _mm256_set1_pd(kernel[13]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 3, j + 1));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 4, j + 1));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[14]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[14]));
                __m256d h_val = _mm256_set1_pd(kernel[14]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 3, j + 2));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 4, j + 2));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            {
                __m256d factor0 = _mm256_add_pd(ymm_j, _mm256_set1_pd(i + kernel_offset[15]));
                __m256d factor1 = _mm256_add_pd(ymm_j, _mm256_set1_pd((i + 1) + kernel_offset[15]));
                __m256d h_val = _mm256_set1_pd(kernel[15]);
                __m256d x0 = _mm256_loadu_pd(&GET_X(i + 3, j + 3));
                __m256d x1 = _mm256_loadu_pd(&GET_X(i + 4, j + 3));
                __m256d abs_x0 = _mm256_and_pd(x0, abs_mask);
                __m256d abs_x1 = _mm256_and_pd(x1, abs_mask);
                ymm_y0 = _mm256_fmadd_pd(_mm256_mul_pd(factor0, h_val), abs_x0, ymm_y0);
                ymm_y1 = _mm256_fmadd_pd(_mm256_mul_pd(factor1, h_val), abs_x1, ymm_y1);
            }
            _mm256_storeu_pd(&GET_Y(i, j), ymm_y0);
            _mm256_storeu_pd(&GET_Y(i + 1, j), ymm_y1);
        }
        for (; j < ON; j++)
        {
            double sum0 = 0.0;
            double sum1 = 0.0;
            for (int k0 = 0; k0 < 4; k0++)
            {
                for (int k1 = 0; k1 < 4; k1++)
                {
                    double factor0 = (double)(i + j + k0 + k1 - 1);
                    double factor1 = (double)((i + 1) + j + k0 + k1 - 1);
                    sum0 += factor0 * GET_H(k0, k1) * fabs(GET_X(i + k0, j + k1));
                    sum1 += factor1 * GET_H(k0, k1) * fabs(GET_X((i + 1) + k0, j + k1));
                }
            }
            GET_Y(i, j) = sum0;
            GET_Y(i + 1, j) = sum1;
        }
    }
    if (i < ON)
    {
        for (int j = 0; j <= ON - 4; j += 4)
        {
            __m256d ymm_y = _mm256_setzero_pd();
            __m256d ymm_j = _mm256_set_pd((double)(j + 3),
                                          (double)(j + 2),
                                          (double)(j + 1),
                                          (double)j);
            for (int k0 = 0; k0 < 4; k0++)
            {
                for (int k1 = 0; k1 < 4; k1++)
                {
                    int idx = k0 * 4 + k1;
                    __m256d factor = _mm256_add_pd(ymm_j,
                                                   _mm256_set1_pd((double)(i + kernel_offset[idx])));
                    __m256d h_val = _mm256_set1_pd(kernel[idx]);
                    __m256d x_val = _mm256_loadu_pd(&GET_X(i + k0, j + k1));
                    __m256d abs_x = _mm256_and_pd(x_val, abs_mask);
                    ymm_y = _mm256_fmadd_pd(_mm256_mul_pd(factor, h_val), abs_x, ymm_y);
                }
            }
            _mm256_storeu_pd(&GET_Y(i, j), ymm_y);
        }
        for (int j = ON - ON % 4; j < ON; j++)
        {
            double sum = 0.0;
            for (int k0 = 0; k0 < 4; k0++)
            {
                for (int k1 = 0; k1 < 4; k1++)
                {
                    double factor = (double)(i + j + k0 + k1 - 1);
                    sum += factor * GET_H(k0, k1) * fabs(GET_X(i + k0, j + k1));
                }
            }
            GET_Y(i, j) = sum;
        }
    }
}

/*
 * Called by the driver to register your functions
 * Use add_function(func, description) to add your own functions
 */
void register_functions()
{
    add_function(&slow_performance1, "slow_performance1");
    add_function(&maxperformance, "maxperformance");
}