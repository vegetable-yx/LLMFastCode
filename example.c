void slow_performance(float *i_A, float *i_x, float *result)
{
    float *tmp_1 = i_A;
    float tmp_2[16 * 16];
    for (int i_2 = 0; i_2 < 16; i_2++)
    {
        for (int j_2 = 0; j_2 < 16; j_2++)
        {
            tmp_2[j_2 * 16 + i_2] = tmp_1[i_2 * 16 + j_2];
        }
    }
    float *tmp_3 = i_A;
    float tmp_4[16 * 16];
    for (int i_4 = 0; i_4 < 16; i_4++)
    {
        for (int k_4 = 0; k_4 < 16; k_4++)
        {
            tmp_4[i_4 * 16 + k_4] = 0;
            for (int j_4 = 0; j_4 < 16; j_4++)
            {
                tmp_4[i_4 * 16 + k_4] += tmp_2[i_4 * 16 + j_4] * tmp_3[j_4 * 16 + k_4];
            }
        }
    }
    float *tmp_5 = i_x;
    float tmp_6[16 * 1];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 1; k_6++)
        {
            tmp_6[i_6 * 1 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 1 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 1 + k_6];
            }
        }
    }
    float tmp_7[16] = {-4.0, 4.0, 9.0, 5.0, 6.0, 7.0, 10.0, -9.0, -2.0, 5.0, 4.0, -10.0, 2.0, -5.0, 8.0, -10.0};
    float tmp_8[16 * 1];
    for (int i_8 = 0; i_8 < 16; i_8++)
    {
        for (int j_8 = 0; j_8 < 1; j_8++)
        {
            tmp_8[i_8 * 1 + j_8] = tmp_6[i_8 * 1 + j_8] + tmp_7[i_8 * 1 + j_8];
        }
    }
    for (int i_8 = 0; i_8 < 16; i_8++)
        result[i_8] = tmp_8[i_8];
}
// i_A float 256
// i_x float 16
// result float 16
