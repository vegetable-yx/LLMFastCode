#include <immintrin.h>
#include "common.h"

/* LLM prompt code start */

void slow_performance(float *i_z_128, float *i_y_32, float *i_y_16, float *i_z_64, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_y_32;
    float tmp_3[16 * 4];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_16;
    float *tmp_5 = i_z_64;
    float tmp_6[2 * 8];
    for (int i_6 = 0; i_6 < 2; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[8 * 2];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 2; k_7++)
        {
            tmp_7[i_7 * 2 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 2 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 2 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 16; i_7++)
        result[i_7] = tmp_7[i_7];
}

/* Max performance function start */
void max_performance(float *i_z_128, float *i_y_32, float *i_y_16, float *i_z_64, float *result)
{
    // Fill your code here.
}
/* Max performance function end */

/* LLM prompt code end */

/*
 * Called by the driver to register your functions
 * Use add_function(func, description) to add your own functions
 */
void register_functions()
{
    add_function(&slow_performance, "slow_performance");
    add_function(&max_performance, "max_performance");
}