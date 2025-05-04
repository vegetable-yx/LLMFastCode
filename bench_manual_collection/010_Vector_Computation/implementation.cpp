#include "common.h"
#include <immintrin.h>
#include <math.h>

#define N 1024

// x, y, z are __attribute__((aligned(32)))
void slow_performance1(double *__restrict x, double *__restrict y, double *__restrict z)
{
    for (int i = 0; i < N; i++)
    {
        double a = i % 2 ? x[i - 1] : x[i + 1];
        double b = y[i];
        if (round(a) > round(b))
        {
            z[i] = a + a * b;
        }
        else
        {
            z[i] = b - 3 * i;
        }
    }
}

// x, y, z are __attribute__((aligned(32)))
void maxperformance(double *__restrict x, double *__restrict y, double *__restrict z)
{
    const __m256i one64 = _mm256_set1_epi64x(1);
    const __m256d three = _mm256_set1_pd(3.0);

    for (int i = 0; i < N; i += 4)
    {
        __m128i idx32 = _mm_set_epi32(i + 3, i + 2, i + 1, i);
        __m256i idx64 = _mm256_cvtepi32_epi64(idx32);

        __m256i parity = _mm256_and_si256(idx64, one64);
        __m256i maskOdd = _mm256_cmpeq_epi64(parity, one64);

        __m256i plus1 = _mm256_add_epi64(idx64, one64);
        __m256i minus1 = _mm256_sub_epi64(idx64, one64);

        __m256i vindex = _mm256_blendv_epi8(plus1, minus1, maskOdd);

        __m256d a = _mm256_i64gather_pd(x, vindex, 8);

        __m256d b = _mm256_load_pd(y + i);

        __m256d ra = _mm256_round_pd(a, _MM_FROUND_NINT | _MM_FROUND_NO_EXC);
        __m256d rb = _mm256_round_pd(b, _MM_FROUND_NINT | _MM_FROUND_NO_EXC);

        __m256d mulAB = _mm256_mul_pd(a, b);
        __m256d expr1 = _mm256_add_pd(a, mulAB);

        __m256d idx_d = _mm256_cvtepi32_pd(idx32);
        __m256d expr2 = _mm256_sub_pd(b, _mm256_mul_pd(idx_d, three));

        __m256d cmpMask = _mm256_cmp_pd(ra, rb, _CMP_GT_OQ);
        __m256d result = _mm256_blendv_pd(expr2, expr1, cmpMask);

        _mm256_store_pd(z + i, result);
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