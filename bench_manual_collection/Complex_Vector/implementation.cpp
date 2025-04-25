#include <immintrin.h>
#include <cmath>
#include "common.h"

using namespace std;

#define N 1024

// Precondition: 0 <= z[i] < 1.0
void slow_performance1(double *x, double *y, double *z)
{
  double t[2];
  for (int i = 0; i < N; i++)
  {
    if (sqrt(x[i * 2] * x[i * 2] + x[i * 2 + 1] * x[i * 2 + 1]) > sqrt(y[i * 2] * y[i * 2] + y[i * 2 + 1] * y[i * 2 + 1]))
    {
      unsigned int k = floor(4.0 * z[i]);
      switch (k)
      {
      case 0:
        t[0] = x[i * 2] + y[i * 2] * 5.1;
        t[1] = x[i * 2 + 1] + y[i * 2 + 1] * 5.1;
        break;
      case 1:
        t[0] = (x[i * 2]) * (y[i * 2] * 2.1) - (x[i * 2 + 1]) * (y[i * 2 + 1] * 2.1);
        t[1] = (x[i * 2]) * (y[i * 2 + 1] * 2.1) + (x[i * 2 + 1]) * (y[i * 2] * 2.1);
        break;
      case 2:
        t[0] = x[i * 2] + y[i * 2] * (-3.5);
        t[1] = x[i * 2 + 1] + y[i * 2 + 1] * (-3.5);
        break;
      case 3:
        t[0] = (x[i * 2]) * (y[i * 2] * (-4.1)) - (x[i * 2 + 1]) * (y[i * 2 + 1] * (-4.1));
        t[1] = (x[i * 2]) * (y[i * 2 + 1] * (-4.1)) + (x[i * 2 + 1]) * (y[i * 2] * (-4.1));
        break;
      default:
        break;
      }
      z[i] += t[0] + ((t[0]) * (t[0]) - (t[1]) * (t[1]));
    }
    else
    {
      z[i] += round(((x[i * 2]) * (x[i * 2]) - (x[i * 2 + 1]) * (x[i * 2 + 1]))) + pow(sqrt(y[i * 2] * y[i * 2] + y[i * 2 + 1] * y[i * 2 + 1]), 2.0);
    }
  }
}

void maxperformance(double *x, double *y, double *z)
{
  const __m256d vzero = _mm256_set1_pd(0.0);
  const __m256d vhalf = _mm256_set1_pd(0.5);
  const __m256d posOne = _mm256_set1_pd(1.0);
  const __m256d negOne = _mm256_set1_pd(-1.0);
  const __m256i absMaskI = _mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF);
  const __m256d absMaskD = _mm256_castsi256_pd(absMaskI);

  const __m256d thresh025 = _mm256_set1_pd(0.25);
  const __m256d thresh050 = _mm256_set1_pd(0.5);
  const __m256d thresh075 = _mm256_set1_pd(0.75);

  const __m256d c5p1 = _mm256_set1_pd(5.1);
  const __m256d c3p5neg = _mm256_set1_pd(-3.5);
  const __m256d c2p1 = _mm256_set1_pd(2.1);
  const __m256d c4p1neg = _mm256_set1_pd(-4.1);

  for (int i = 0; i < N; i += 4)
  {
    __m256d x0 = _mm256_load_pd((const double *)&x[i * 2 + 0]);
    __m256d x1 = _mm256_load_pd((const double *)&x[i * 2 + 4]);
    __m256d y0 = _mm256_load_pd((const double *)&y[i * 2 + 0]);
    __m256d y1 = _mm256_load_pd((const double *)&y[i * 2 + 4]);

    __m256d zval = _mm256_load_pd(&z[i]);
    zval = _mm256_permute4x64_pd(zval, 0b11011000);

    __m256d xRe = _mm256_shuffle_pd(x0, x1, 0x0);
    __m256d xIm = _mm256_shuffle_pd(x0, x1, 0xF);
    __m256d yRe = _mm256_shuffle_pd(y0, y1, 0x0);
    __m256d yIm = _mm256_shuffle_pd(y0, y1, 0xF);

    __m256d xRe2 = _mm256_mul_pd(xRe, xRe);
    __m256d xIm2 = _mm256_mul_pd(xIm, xIm);
    __m256d xabs2 = _mm256_add_pd(xRe2, xIm2);
    __m256d yRe2 = _mm256_mul_pd(yRe, yRe);
    __m256d yIm2 = _mm256_mul_pd(yIm, yIm);
    __m256d yabs2 = _mm256_add_pd(yRe2, yIm2);
    __m256d branchMask = _mm256_cmp_pd(xabs2, yabs2, _CMP_GT_OQ);

    __m256d mask0 = _mm256_cmp_pd(zval, thresh025, _CMP_LT_OQ);
    __m256d mask1 = _mm256_and_pd(_mm256_cmp_pd(zval, thresh025, _CMP_GE_OQ),
                                  _mm256_cmp_pd(zval, thresh050, _CMP_LT_OQ));
    __m256d mask2 = _mm256_and_pd(_mm256_cmp_pd(zval, thresh050, _CMP_GE_OQ),
                                  _mm256_cmp_pd(zval, thresh075, _CMP_LT_OQ));
    __m256d mask3 = _mm256_cmp_pd(zval, thresh075, _CMP_GE_OQ);

    __m256d addMask = _mm256_or_pd(mask0, mask2);

    __m256d c_add = _mm256_blendv_pd(c5p1, c3p5neg, _mm256_cmp_pd(zval, thresh050, _CMP_GE_OQ));
    __m256d c_mult = _mm256_blendv_pd(c2p1, c4p1neg, _mm256_cmp_pd(zval, thresh075, _CMP_GE_OQ));

    __m256d tRe_add = _mm256_fmadd_pd(c_add, yRe, xRe);
    __m256d tIm_add = _mm256_fmadd_pd(c_add, yIm, xIm);
    __m256d candidate_add = _mm256_fnmadd_pd(tIm_add, tIm_add, _mm256_fmadd_pd(tRe_add, tRe_add, tRe_add));

    __m256d cyRe = _mm256_mul_pd(c_mult, yRe);
    __m256d cyIm = _mm256_mul_pd(c_mult, yIm);
    __m256d tRe_mult = _mm256_fmsub_pd(xRe, cyRe, _mm256_mul_pd(xIm, cyIm));
    __m256d tIm_mult = _mm256_fmadd_pd(xRe, cyIm, _mm256_mul_pd(xIm, cyRe));
    __m256d candidate_mult = _mm256_fnmadd_pd(tIm_mult, tIm_mult, _mm256_fmadd_pd(tRe_mult, tRe_mult, tRe_mult));

    __m256d candidate = _mm256_blendv_pd(candidate_mult, candidate_add, addMask);

    __m256d re_x2 = _mm256_sub_pd(xRe2, xIm2);
    __m256d isNeg = _mm256_cmp_pd(re_x2, vzero, _CMP_LT_OQ);
    __m256d signVal = _mm256_blendv_pd(posOne, negOne, isNeg);
    __m256d absVal = _mm256_and_pd(re_x2, absMaskD);
    __m256d tmp = _mm256_add_pd(absVal, vhalf);
    __m256d floored = _mm256_floor_pd(tmp);
    __m256d re_x2_rounded = _mm256_mul_pd(signVal, floored);
    __m256d else_val = _mm256_add_pd(re_x2_rounded, yabs2);

    __m256d totalAdd = _mm256_blendv_pd(else_val, candidate, branchMask);
    __m256d zout = _mm256_add_pd(zval, totalAdd);

    zout = _mm256_permute4x64_pd(zout, 0b11011000);
    _mm256_store_pd(&z[i], zout);
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