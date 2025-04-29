#include "common.h"
#include <immintrin.h>
#include <math.h>

#define NC 32
#define NR 64

void slow_performance1(double *x __attribute__((aligned(32))), double *A __attribute__((aligned(32))), double *y __attribute__((aligned(32))))
{
    for (int j = 0; j < NC; j++)
        y[j] = 0;

    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            y[j] += A[i * NC + j] * x[i];
        }
    }
}

void maxperformance(double *x __attribute__((aligned(32))), double *A __attribute__((aligned(32))), double *y __attribute__((aligned(32))))
{
    __m256d y0 = _mm256_setzero_pd();
    __m256d y1 = _mm256_setzero_pd();
    __m256d y2 = _mm256_setzero_pd();
    __m256d y3 = _mm256_setzero_pd();
    __m256d y4 = _mm256_setzero_pd();
    __m256d y5 = _mm256_setzero_pd();
    __m256d y6 = _mm256_setzero_pd();
    __m256d y7 = _mm256_setzero_pd();

    for (int i = 0; i < NR; ++i)
    {
        __m256d xi = _mm256_broadcast_sd(x + i);
        const double *Ai = A + (size_t)i * NC;
        __m256d a;

        a = _mm256_load_pd(Ai + 0);

        y0 = _mm256_add_pd(y0, _mm256_mul_pd(a, xi));
        a = _mm256_load_pd(Ai + 4);
        y1 = _mm256_add_pd(y1, _mm256_mul_pd(a, xi));

        a = _mm256_load_pd(Ai + 8);
        y2 = _mm256_add_pd(y2, _mm256_mul_pd(a, xi));

        a = _mm256_load_pd(Ai + 12);
        y3 = _mm256_add_pd(y3, _mm256_mul_pd(a, xi));

        a = _mm256_load_pd(Ai + 16);
        y4 = _mm256_add_pd(y4, _mm256_mul_pd(a, xi));

        a = _mm256_load_pd(Ai + 20);
        y5 = _mm256_add_pd(y5, _mm256_mul_pd(a, xi));

        a = _mm256_load_pd(Ai + 24);
        y6 = _mm256_add_pd(y6, _mm256_mul_pd(a, xi));

        a = _mm256_load_pd(Ai + 28);
        y7 = _mm256_add_pd(y7, _mm256_mul_pd(a, xi));
    }

    _mm256_store_pd(y + 0, y0);
    _mm256_store_pd(y + 4, y1);
    _mm256_store_pd(y + 8, y2);
    _mm256_store_pd(y + 12, y3);
    _mm256_store_pd(y + 16, y4);
    _mm256_store_pd(y + 20, y5);
    _mm256_store_pd(y + 24, y6);
    _mm256_store_pd(y + 28, y7);
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