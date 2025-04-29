#include <immintrin.h>
#include "common.h"

void slow_performance(double* x, double* y, double* A) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            double a = x[4 * i + 0];
            double b = x[4 * i + 1];
            double c = x[4 * i + 2];
            double d = x[4 * i + 3];

            double e = y[4 * j + 0];
            double f = y[4 * j + 1];
            double g = y[4 * j + 2];
            double h = y[4 * j + 3];

            // Quaternion multiplication:
            // (a + bi + cj + dk) * (e + fi + gj + hk) =
            // (ae - bf - cg - dh) +
            // (af + be + ch - dg)i +
            // (ag - bh + ce + df)j +
            // (ah + bg - cf + de)k
            double r0 = a * e - b * f - c * g - d * h;
            double r1 = a * f + b * e + c * h - d * g;
            double r2 = a * g - b * h + c * e + d * f;
            double r3 = a * h + b * g - c * f + d * e;

            int index = 4 * (i * 2 + j);
            A[index + 0] = r0;
            A[index + 1] = r1;
            A[index + 2] = r2;
            A[index + 3] = r3;
        }
    }
}

void maxperformance(double* x, double* y, double* A) {
    // Load all x values at once - better cache utilization
    __m256d x0 = _mm256_loadu_pd(&x[0]); // [x[0], x[1], x[2], x[3]]
    __m256d x4 = _mm256_loadu_pd(&x[4]); // [x[4], x[5], x[6], x[7]]
    
    // Process first row (i=0)
    {
        // j=0 case
        __m256d y0 = _mm256_loadu_pd(&y[0]); // [y[0], y[1], y[2], y[3]]
        
        // Prepare shuffled versions for SIMD quaternion multiplication
        __m256d a_bcda = _mm256_permute4x64_pd(x0, 0x00); // broadcast a (x[0])
        __m256d b_cdab = _mm256_permute4x64_pd(x0, 0x93); // [b, c, d, a]
        __m256d c_dabc = _mm256_permute4x64_pd(x0, 0x4E); // [c, d, a, b]
        __m256d d_abcd = _mm256_permute4x64_pd(x0, 0x39); // [d, a, b, c]
        
        // Prepare signs for quaternion multiplication
        __m256d signs1 = _mm256_setr_pd(1.0, 1.0, 1.0, 1.0);
        __m256d signs2 = _mm256_setr_pd(-1.0, 1.0, -1.0, 1.0);
        __m256d signs3 = _mm256_setr_pd(-1.0, 1.0, 1.0, -1.0);
        __m256d signs4 = _mm256_setr_pd(-1.0, -1.0, 1.0, 1.0);
        
        // Shuffle y for different terms
        __m256d y_efgh = y0;                                // [e, f, g, h]
        __m256d y_fghe = _mm256_permute4x64_pd(y0, 0x93);   // [f, g, h, e]
        __m256d y_ghef = _mm256_permute4x64_pd(y0, 0x4E);   // [g, h, e, f]
        __m256d y_hefg = _mm256_permute4x64_pd(y0, 0x39);   // [h, e, f, g]
        
        // Calculate products and apply signs
        __m256d term1 = _mm256_mul_pd(_mm256_mul_pd(a_bcda, y_efgh), signs1);
        __m256d term2 = _mm256_mul_pd(_mm256_mul_pd(b_cdab, y_fghe), signs2);
        __m256d term3 = _mm256_mul_pd(_mm256_mul_pd(c_dabc, y_ghef), signs3);
        __m256d term4 = _mm256_mul_pd(_mm256_mul_pd(d_abcd, y_hefg), signs4);
        
        // Sum all products to get result
        __m256d result = _mm256_add_pd(_mm256_add_pd(term1, term2), 
                                       _mm256_add_pd(term3, term4));
        
        // Store result directly
        _mm256_storeu_pd(&A[0], result);
        
        // j=1 case - reuse all the x shuffles
        y0 = _mm256_loadu_pd(&y[4]); // [y[4], y[5], y[6], y[7]]
        
        // Update y shuffles
        y_efgh = y0;                                // [e, f, g, h]
        y_fghe = _mm256_permute4x64_pd(y0, 0x93);   // [f, g, h, e]
        y_ghef = _mm256_permute4x64_pd(y0, 0x4E);   // [g, h, e, f]
        y_hefg = _mm256_permute4x64_pd(y0, 0x39);   // [h, e, f, g]
        
        // Calculate products and apply signs
        term1 = _mm256_mul_pd(_mm256_mul_pd(a_bcda, y_efgh), signs1);
        term2 = _mm256_mul_pd(_mm256_mul_pd(b_cdab, y_fghe), signs2);
        term3 = _mm256_mul_pd(_mm256_mul_pd(c_dabc, y_ghef), signs3);
        term4 = _mm256_mul_pd(_mm256_mul_pd(d_abcd, y_hefg), signs4);
        
        // Sum all products to get result
        result = _mm256_add_pd(_mm256_add_pd(term1, term2), 
                              _mm256_add_pd(term3, term4));
        
        // Store result directly
        _mm256_storeu_pd(&A[4], result);
    }
    
    // Process second row (i=1)
    {
        // j=0 case
        __m256d y0 = _mm256_loadu_pd(&y[0]); // [y[0], y[1], y[2], y[3]]
        
        // Prepare shuffled versions for SIMD quaternion multiplication
        __m256d a_bcda = _mm256_permute4x64_pd(x4, 0x00); // broadcast a (x[4])
        __m256d b_cdab = _mm256_permute4x64_pd(x4, 0x93); // [b, c, d, a]
        __m256d c_dabc = _mm256_permute4x64_pd(x4, 0x4E); // [c, d, a, b]
        __m256d d_abcd = _mm256_permute4x64_pd(x4, 0x39); // [d, a, b, c]
        
        // Prepare signs for quaternion multiplication
        __m256d signs1 = _mm256_setr_pd(1.0, 1.0, 1.0, 1.0);
        __m256d signs2 = _mm256_setr_pd(-1.0, 1.0, -1.0, 1.0);
        __m256d signs3 = _mm256_setr_pd(-1.0, 1.0, 1.0, -1.0);
        __m256d signs4 = _mm256_setr_pd(-1.0, -1.0, 1.0, 1.0);
        
        // Shuffle y for different terms
        __m256d y_efgh = y0;                                // [e, f, g, h]
        __m256d y_fghe = _mm256_permute4x64_pd(y0, 0x93);   // [f, g, h, e]
        __m256d y_ghef = _mm256_permute4x64_pd(y0, 0x4E);   // [g, h, e, f]
        __m256d y_hefg = _mm256_permute4x64_pd(y0, 0x39);   // [h, e, f, g]
        
        // Calculate products and apply signs
        __m256d term1 = _mm256_mul_pd(_mm256_mul_pd(a_bcda, y_efgh), signs1);
        __m256d term2 = _mm256_mul_pd(_mm256_mul_pd(b_cdab, y_fghe), signs2);
        __m256d term3 = _mm256_mul_pd(_mm256_mul_pd(c_dabc, y_ghef), signs3);
        __m256d term4 = _mm256_mul_pd(_mm256_mul_pd(d_abcd, y_hefg), signs4);
        
        // Sum all products to get result
        __m256d result = _mm256_add_pd(_mm256_add_pd(term1, term2), 
                                      _mm256_add_pd(term3, term4));
        
        // Store result directly
        _mm256_storeu_pd(&A[8], result);
        
        // j=1 case - reuse all the x shuffles
        y0 = _mm256_loadu_pd(&y[4]); // [y[4], y[5], y[6], y[7]]
        
        // Update y shuffles
        y_efgh = y0;                                // [e, f, g, h]
        y_fghe = _mm256_permute4x64_pd(y0, 0x93);   // [f, g, h, e]
        y_ghef = _mm256_permute4x64_pd(y0, 0x4E);   // [g, h, e, f]
        y_hefg = _mm256_permute4x64_pd(y0, 0x39);   // [h, e, f, g]
        
        // Calculate products and apply signs
        term1 = _mm256_mul_pd(_mm256_mul_pd(a_bcda, y_efgh), signs1);
        term2 = _mm256_mul_pd(_mm256_mul_pd(b_cdab, y_fghe), signs2);
        term3 = _mm256_mul_pd(_mm256_mul_pd(c_dabc, y_ghef), signs3);
        term4 = _mm256_mul_pd(_mm256_mul_pd(d_abcd, y_hefg), signs4);
        
        // Sum all products to get result
        result = _mm256_add_pd(_mm256_add_pd(term1, term2), 
                              _mm256_add_pd(term3, term4));
        
        // Store result directly
        _mm256_storeu_pd(&A[12], result);
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