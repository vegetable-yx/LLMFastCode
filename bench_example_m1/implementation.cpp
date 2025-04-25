// #include <immintrin.h>
#include "common.h"

void slow_performance1(complex_t x[4][4], complex_t y[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            y[i][j].re = x[j][i].re;
            y[i][j].im = -x[j][i].im;
        }
    }
}

void maxperformance(complex_t x[4][4], complex_t y[4][4])
{
    slow_performance1(x, y);
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