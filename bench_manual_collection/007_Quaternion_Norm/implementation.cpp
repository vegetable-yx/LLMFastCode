#include "common.h"
#include <immintrin.h>
#include <math.h>

#define N 1024
// x, y, z are __attribute__((aligned(32)))
void slow_performance1(double *__restrict x, double *__restrict y)
{
    const double _c[4] = {2.0, 5.0, 0.25, 0.75};
    const double c0 = _c[0], c1 = _c[1], c2 = _c[2], c3 = _c[3];
    for (size_t i = 0; i < N; ++i)
    {
        double *xi = &(x[i * 4]);
        double a = c0 * xi[0] - c1 * xi[1] - c2 * xi[2] - c3 * xi[3];
        double b = c0 * xi[1] + c1 * xi[0] + c2 * xi[3] - c3 * xi[2];
        double c = c0 * xi[2] - c1 * xi[3] + c2 * xi[0] + c3 * xi[1];
        double d = c0 * xi[3] + c1 * xi[2] - c2 * xi[1] + c3 * xi[0];
        y[i] = a * a + b * b + c * c + d * d;
    }
}

// x, y, z are __attribute__((aligned(32)))
void maxperformance(double *__restrict x, double *__restrict y)
{
    const double norm2_q = 29.625;
    __m256d coeff = _mm256_set1_pd(norm2_q);

    for (size_t i = 0; i < N; ++i)
    {
        __m256d v = _mm256_load_pd(x + 4 * i);
        __m256d sq = _mm256_mul_pd(v, v);

        __m128d lo = _mm256_castpd256_pd128(sq);
        __m128d hi = _mm256_extractf128_pd(sq, 1);
        __m128d sum2 = _mm_add_pd(lo, hi);

        __m128d shuf = _mm_shuffle_pd(sum2, sum2, 0x1);
        __m128d tot = _mm_add_pd(sum2, shuf);

        double xsq = _mm_cvtsd_f64(tot);
        y[i] = xsq * norm2_q;
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