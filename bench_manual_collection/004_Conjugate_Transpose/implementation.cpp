#include <immintrin.h>
#include "common.h"

void slow_performance1(double *__restrict x, double *__restrict y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // y[i][j].re = x[j][i].re;
            // y[i][j].im = -x[j][i].im;
            y[i * 8 + j * 2] = x[j * 8 + i * 2];
            y[i * 8 + j * 2 + 1] = -x[j * 8 + i * 2 + 1];
        }
    }
}

void maxperformance(double *__restrict x, double *__restrict y)
{
    __m256d sign_mask = _mm256_set_pd(-0.0, 0.0, -0.0, 0.0);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            __m256d r0 = _mm256_load_pd(&x[(i * 2 + 0) * 8 + (j * 2) * 2]);
            __m256d r1 = _mm256_load_pd(&x[(i * 2 + 1) * 8 + (j * 2) * 2]);
            __m256d nr0 = _mm256_xor_pd(r0, sign_mask);
            __m256d nr1 = _mm256_xor_pd(r1, sign_mask);
            nr1 = _mm256_permute4x64_pd(nr1, 0b01001110);
            __m256d res0 = _mm256_blend_pd(nr0, nr1, 0b1100);
            __m256d res1 = _mm256_blend_pd(nr0, nr1, 0b0011);
            res1 = _mm256_permute4x64_pd(res1, 0b01001110);
            _mm256_store_pd(&y[(j * 2 + 0) * 8 + (i * 2) * 2], res0);
            _mm256_store_pd(&y[(j * 2 + 1) * 8 + (i * 2) * 2], res1);
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