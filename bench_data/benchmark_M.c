// i_x_512 float 512
// i_y_64 float 64
// i_z_192 float 192
// result float 384
void slow_performance(float *i_x_512, float *i_y_64, float *i_z_192, float *result)
{
    float *tmp_1 = i_x_512;
    float *tmp_2 = i_y_64;
    float tmp_3[32 * 4];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_192;
    float tmp_5[1 * 192];
    for (int i_5 = 0; i_5 < 1; i_5++)
    {
        for (int j_5 = 0; j_5 < 192; j_5++)
        {
            tmp_5[j_5 * 1 + i_5] = tmp_4[i_5 * 192 + j_5];
        }
    }
    float tmp_6[16 * 24];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 24; k_6++)
        {
            tmp_6[i_6 * 24 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 24 + k_6] += tmp_3[i_6 * 8 + j_6] * tmp_5[j_6 * 24 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 384; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_x_512 float 512
// i_x_128 float 128
// i_z_1024 float 1024
// i_z_64 float 64
// result float 1024
void slow_performance(float *i_x_512, float *i_x_128, float *i_z_1024, float *i_z_64, float *result)
{
    float *tmp_1 = i_x_512;
    float *tmp_2 = i_x_128;
    float tmp_3[32 * 8];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_1024;
    float *tmp_5 = i_z_64;
    float tmp_6[128 * 8];
    for (int i_6 = 0; i_6 < 128; i_6++)
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
    float tmp_7[16 * 64];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_384 float 384
// i_z_512 float 512
// i_z_128 float 128
// result float 64
void slow_performance(float *i_z_384, float *i_z_512, float *i_z_128, float *result)
{
    float *tmp_1 = i_z_384;
    float *tmp_2 = i_z_512;
    float tmp_3[12 * 16];
    for (int i_3 = 0; i_3 < 12; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_128;
    float *tmp_5 = i_z_384;
    float tmp_6[16 * 48];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 48; k_6++)
        {
            tmp_6[i_6 * 48 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 48 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 48 + k_6];
            }
        }
    }
    float tmp_7[4 * 16];
    for (int i_7 = 0; i_7 < 4; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 48; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 48 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_256 float 256
// i_z_1024 float 1024
// i_z_768 float 768
// result float 1024
void slow_performance(float *i_y_256, float *i_z_1024, float *i_z_768, float *result)
{
    float *tmp_1 = i_y_256;
    float *tmp_2 = i_z_1024;
    float tmp_3[8 * 32];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_768;
    float *tmp_5 = i_z_768;
    float tmp_6[16 * 16];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 48; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 48 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[32 * 32];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_1024 float 1024
// i_y_384 float 384
// i_z_64 float 64
// result float 1024
void slow_performance(float *i_x_1024, float *i_y_384, float *i_z_64, float *result)
{
    float *tmp_1 = i_x_1024;
    float *tmp_2 = i_y_384;
    float tmp_3[32 * 12];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 12; k_3++)
        {
            tmp_3[i_3 * 12 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 12 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 12 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_z_64;
    float tmp_6[48 * 8];
    for (int i_6 = 0; i_6 < 48; i_6++)
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
    float tmp_7[32 * 32];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 12; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 12 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_192 float 192
// i_z_1024 float 1024
// i_x_128 float 128
// result float 512
void slow_performance(float *i_x_192, float *i_z_1024, float *i_x_128, float *result)
{
    float *tmp_1 = i_x_192;
    float *tmp_2 = i_x_192;
    float tmp_3[8 * 8];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 24; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 24 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_1024;
    float *tmp_5 = i_x_128;
    float tmp_6[64 * 8];
    for (int i_6 = 0; i_6 < 64; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[8 * 64];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_64 float 64
// i_z_768 float 768
// i_z_384 float 384
// result float 128
void slow_performance(float *i_y_64, float *i_z_768, float *i_z_384, float *result)
{
    float *tmp_1 = i_y_64;
    float *tmp_2 = i_z_768;
    float tmp_3[8 * 96];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 96; k_3++)
        {
            tmp_3[i_3 * 96 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 96 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 96 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_64;
    float *tmp_5 = i_z_384;
    float tmp_6[8 * 48];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 48; k_6++)
        {
            tmp_6[i_6 * 48 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 48 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 48 + k_6];
            }
        }
    }
    float tmp_7[16 * 8];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 48; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 48 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_192 float 192
// i_x_64 float 64
// result float 256
void slow_performance(float *i_y_192, float *i_x_64, float *result)
{
    float *tmp_1 = i_y_192;
    float *tmp_2 = i_y_192;
    float tmp_3[8 * 24];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int j_3 = 0; j_3 < 24; j_3++)
        {
            tmp_3[i_3 * 24 + j_3] = tmp_1[i_3 * 24 + j_3] + tmp_2[i_3 * 24 + j_3];
        }
    }
    float *tmp_4 = i_y_192;
    float *tmp_5 = i_x_64;
    float tmp_6[24 * 8];
    for (int i_6 = 0; i_6 < 24; i_6++)
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
    float tmp_7[16 * 16];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 12; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 12 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_256 float 256
// i_z_768 float 768
// result float 1024
void slow_performance(float *i_z_256, float *i_z_768, float *result)
{
    float *tmp_1 = i_z_256;
    float *tmp_2 = i_z_256;
    float tmp_3[128 * 2];
    for (int i_3 = 0; i_3 < 128; i_3++)
    {
        for (int j_3 = 0; j_3 < 2; j_3++)
        {
            tmp_3[i_3 * 2 + j_3] = tmp_1[i_3 * 2 + j_3] + tmp_2[i_3 * 2 + j_3];
        }
    }
    float *tmp_4 = i_z_768;
    float *tmp_5 = i_z_768;
    float tmp_6[16 * 16];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 48; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 48 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[32 * 32];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_256 float 256
// i_y_192 float 192
// i_x_1024 float 1024
// result float 192
void slow_performance(float *i_y_256, float *i_y_192, float *i_x_1024, float *result)
{
    float *tmp_1 = i_y_256;
    float *tmp_2 = i_y_256;
    float tmp_3[2 * 128];
    for (int i_3 = 0; i_3 < 2; i_3++)
    {
        for (int j_3 = 0; j_3 < 128; j_3++)
        {
            tmp_3[i_3 * 128 + j_3] = tmp_1[i_3 * 128 + j_3] + tmp_2[i_3 * 128 + j_3];
        }
    }
    float *tmp_4 = i_y_192;
    float *tmp_5 = i_x_1024;
    float tmp_6[12 * 64];
    for (int i_6 = 0; i_6 < 12; i_6++)
    {
        for (int k_6 = 0; k_6 < 64; k_6++)
        {
            tmp_6[i_6 * 64 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 64 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 64 + k_6];
            }
        }
    }
    float tmp_7[8 * 24];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 24; k_7++)
        {
            tmp_7[i_7 * 24 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 24 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 24 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_256 float 256
// i_y_64 float 64
// result float 256
void slow_performance(float *i_z_256, float *i_y_64, float *result)
{
    float *tmp_1 = i_z_256;
    float *tmp_2 = i_y_64;
    float *tmp_3 = i_z_256;
    float tmp_4[16 * 64];
    for (int i_4 = 0; i_4 < 16; i_4++)
    {
        for (int k_4 = 0; k_4 < 64; k_4++)
        {
            tmp_4[i_4 * 64 + k_4] = 0;
            for (int j_4 = 0; j_4 < 4; j_4++)
            {
                tmp_4[i_4 * 64 + k_4] += tmp_2[i_4 * 4 + j_4] * tmp_3[j_4 * 64 + k_4];
            }
        }
    }
    float tmp_5[8 * 32];
    for (int i_5 = 0; i_5 < 8; i_5++)
    {
        for (int k_5 = 0; k_5 < 32; k_5++)
        {
            tmp_5[i_5 * 32 + k_5] = 0;
            for (int j_5 = 0; j_5 < 32; j_5++)
            {
                tmp_5[i_5 * 32 + k_5] += tmp_1[i_5 * 32 + j_5] * tmp_4[j_5 * 32 + k_5];
            }
        }
    }
    for (int i_5 = 0; i_5 < 256; i_5++)
        result[i_5] = tmp_5[i_5];
}
/**********************************************************************************/
// i_z_1024 float 1024
// i_x_512 float 512
// i_y_256 float 256
// result float 64
void slow_performance(float *i_z_1024, float *i_x_512, float *i_y_256, float *result)
{
    float *tmp_1 = i_z_1024;
    float *tmp_2 = i_x_512;
    float tmp_3[32 * 16];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_256;
    float *tmp_5 = i_x_512;
    float tmp_6[8 * 16];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[16 * 4];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 4; k_7++)
        {
            tmp_7[i_7 * 4 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 4 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 4 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_128 float 128
// i_x_256 float 256
// i_x_64 float 64
// i_y_192 float 192
// result float 384
void slow_performance(float *i_z_128, float *i_x_256, float *i_x_64, float *i_y_192, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_x_256;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_64;
    float *tmp_5 = i_y_192;
    float tmp_6[8 * 24];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 24; k_6++)
        {
            tmp_6[i_6 * 24 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 24 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 24 + k_6];
            }
        }
    }
    float tmp_7[32 * 12];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 12; k_7++)
        {
            tmp_7[i_7 * 12 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 12 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 12 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_768 float 768
// i_y_384 float 384
// i_x_64 float 64
// i_x_1024 float 1024
// result float 512
void slow_performance(float *i_y_768, float *i_y_384, float *i_x_64, float *i_x_1024, float *result)
{
    float *tmp_1 = i_y_768;
    float *tmp_2 = i_y_384;
    float tmp_3[32 * 16];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 24; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 24 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_64;
    float *tmp_5 = i_x_1024;
    float tmp_6[8 * 128];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 128; k_6++)
        {
            tmp_6[i_6 * 128 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 128 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 128 + k_6];
            }
        }
    }
    float tmp_7[16 * 32];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_1024 float 1024
// i_z_256 float 256
// result float 1024
void slow_performance(float *i_y_1024, float *i_z_256, float *result)
{
    float *tmp_1 = i_y_1024;
    float *tmp_2 = i_z_256;
    float tmp_3[16 * 4];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 64; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 64 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_256;
    float *tmp_5 = i_z_256;
    float tmp_6[32 * 32];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[8 * 128];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 128; k_7++)
        {
            tmp_7[i_7 * 128 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 128 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 128 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_256 float 256
// i_x_128 float 128
// i_z_512 float 512
// result float 1024
void slow_performance(float *i_x_256, float *i_x_128, float *i_z_512, float *result)
{
    float *tmp_1 = i_x_256;
    float tmp_2[1 * 256];
    for (int i_2 = 0; i_2 < 1; i_2++)
    {
        for (int j_2 = 0; j_2 < 256; j_2++)
        {
            tmp_2[j_2 * 1 + i_2] = tmp_1[i_2 * 256 + j_2];
        }
    }
    float *tmp_3 = i_x_128;
    float *tmp_4 = i_z_512;
    float tmp_5[8 * 32];
    for (int i_5 = 0; i_5 < 8; i_5++)
    {
        for (int k_5 = 0; k_5 < 32; k_5++)
        {
            tmp_5[i_5 * 32 + k_5] = 0;
            for (int j_5 = 0; j_5 < 16; j_5++)
            {
                tmp_5[i_5 * 32 + k_5] += tmp_3[i_5 * 16 + j_5] * tmp_4[j_5 * 32 + k_5];
            }
        }
    }
    float tmp_6[32 * 32];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_2[i_6 * 8 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 1024; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_384 float 384
// i_y_128 float 128
// i_y_1024 float 1024
// result float 768
void slow_performance(float *i_z_384, float *i_y_128, float *i_y_1024, float *result)
{
    float *tmp_1 = i_z_384;
    float *tmp_2 = i_y_128;
    float tmp_3[48 * 16];
    for (int i_3 = 0; i_3 < 48; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_1024;
    float *tmp_5 = i_y_1024;
    float tmp_6[16 * 16];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 64; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 64 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[48 * 16];
    for (int i_7 = 0; i_7 < 48; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 768; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_128 float 128
// i_y_384 float 384
// i_z_64 float 64
// i_z_256 float 256
// result float 192
void slow_performance(float *i_y_128, float *i_y_384, float *i_z_64, float *i_z_256, float *result)
{
    float *tmp_1 = i_y_128;
    float *tmp_2 = i_y_384;
    float tmp_3[16 * 48];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 48; k_3++)
        {
            tmp_3[i_3 * 48 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 48 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 48 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_64;
    float *tmp_5 = i_z_256;
    float tmp_6[16 * 64];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 64; k_6++)
        {
            tmp_6[i_6 * 64 + k_6] = 0;
            for (int j_6 = 0; j_6 < 4; j_6++)
            {
                tmp_6[i_6 * 64 + k_6] += tmp_4[i_6 * 4 + j_6] * tmp_5[j_6 * 64 + k_6];
            }
        }
    }
    float tmp_7[12 * 16];
    for (int i_7 = 0; i_7 < 12; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 64; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 64 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_64 float 64
// i_x_1024 float 1024
// i_x_192 float 192
// i_z_128 float 128
// result float 384
void slow_performance(float *i_z_64, float *i_x_1024, float *i_x_192, float *i_z_128, float *result)
{
    float *tmp_1 = i_z_64;
    float *tmp_2 = i_x_1024;
    float tmp_3[8 * 128];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 128; k_3++)
        {
            tmp_3[i_3 * 128 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 128 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 128 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_192;
    float *tmp_5 = i_z_128;
    float tmp_6[24 * 16];
    for (int i_6 = 0; i_6 < 24; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[32 * 12];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 12; k_7++)
        {
            tmp_7[i_7 * 12 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 12 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 12 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_768 float 768
// i_z_192 float 192
// i_z_64 float 64
// i_y_1024 float 1024
// result float 256
void slow_performance(float *i_y_768, float *i_z_192, float *i_z_64, float *i_y_1024, float *result)
{
    float *tmp_1 = i_y_768;
    float *tmp_2 = i_z_192;
    float tmp_3[16 * 4];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 48; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 48 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_64;
    float *tmp_5 = i_y_1024;
    float tmp_6[8 * 128];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 128; k_6++)
        {
            tmp_6[i_6 * 128 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 128 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 128 + k_6];
            }
        }
    }
    float tmp_7[4 * 64];
    for (int i_7 = 0; i_7 < 4; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_64 float 64
// i_y_384 float 384
// i_y_128 float 128
// i_z_256 float 256
// result float 192
void slow_performance(float *i_x_64, float *i_y_384, float *i_y_128, float *i_z_256, float *result)
{
    float *tmp_1 = i_x_64;
    float *tmp_2 = i_y_384;
    float tmp_3[8 * 48];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 48; k_3++)
        {
            tmp_3[i_3 * 48 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 48 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 48 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_128;
    float *tmp_5 = i_z_256;
    float tmp_6[8 * 16];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[24 * 8];
    for (int i_7 = 0; i_7 < 24; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_128 float 128
// i_y_512 float 512
// i_y_768 float 768
// i_z_64 float 64
// result float 768
void slow_performance(float *i_x_128, float *i_y_512, float *i_y_768, float *i_z_64, float *result)
{
    float *tmp_1 = i_x_128;
    float *tmp_2 = i_y_512;
    float tmp_3[8 * 32];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_768;
    float *tmp_5 = i_z_64;
    float tmp_6[96 * 8];
    for (int i_6 = 0; i_6 < 96; i_6++)
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
    float tmp_7[16 * 48];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 48; k_7++)
        {
            tmp_7[i_7 * 48 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 48 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 48 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 768; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_1024 float 1024
// i_y_512 float 512
// result float 512
void slow_performance(float *i_y_1024, float *i_y_512, float *result)
{
    float *tmp_1 = i_y_1024;
    float *tmp_2 = i_y_1024;
    float tmp_3[32 * 32];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_512;
    float *tmp_5 = i_y_1024;
    float tmp_6[16 * 32];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[32 * 16];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_192 float 192
// i_y_384 float 384
// result float 512
void slow_performance(float *i_y_192, float *i_y_384, float *result)
{
    float *tmp_1 = i_y_192;
    float *tmp_2 = i_y_192;
    float tmp_3[8 * 8];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 24; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 24 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_y_192;
    float tmp_6[32 * 16];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 12; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 12 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[8 * 64];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_1024 float 1024
// i_z_128 float 128
// i_y_512 float 512
// result float 512
void slow_performance(float *i_y_1024, float *i_z_128, float *i_y_512, float *result)
{
    float *tmp_1 = i_y_1024;
    float *tmp_2 = i_z_128;
    float tmp_3[32 * 4];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_512;
    float *tmp_5 = i_y_512;
    float tmp_6[32 * 32];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[8 * 64];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_64 float 64
// i_z_384 float 384
// result float 256
void slow_performance(float *i_z_64, float *i_z_384, float *result)
{
    float *tmp_1 = i_z_64;
    float *tmp_2 = i_z_64;
    float tmp_3[32 * 32];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 2; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 2 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_384;
    float *tmp_5 = i_z_384;
    float tmp_6[16 * 16];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[32 * 8];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_128 float 128
// i_z_64 float 64
// i_z_192 float 192
// result float 128
void slow_performance(float *i_z_128, float *i_z_64, float *i_z_192, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_z_64;
    float tmp_3[32 * 16];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 4; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 4 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_192;
    float *tmp_5 = i_z_192;
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[32 * 4];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 4; k_7++)
        {
            tmp_7[i_7 * 4 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 4 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 4 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_384 float 384
// i_y_192 float 192
// result float 1024
void slow_performance(float *i_y_384, float *i_y_192, float *result)
{
    float *tmp_1 = i_y_384;
    float *tmp_2 = i_y_192;
    float tmp_3[16 * 8];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 24; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 24 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_y_192;
    float tmp_6[32 * 16];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 12; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 12 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[16 * 64];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_256 float 256
// i_x_192 float 192
// i_z_512 float 512
// result float 384
void slow_performance(float *i_y_256, float *i_x_192, float *i_z_512, float *result)
{
    float *tmp_1 = i_y_256;
    float *tmp_2 = i_x_192;
    float tmp_3[32 * 24];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 24; k_3++)
        {
            tmp_3[i_3 * 24 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 24 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 24 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_256;
    float *tmp_5 = i_z_512;
    float tmp_6[8 * 16];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[48 * 8];
    for (int i_7 = 0; i_7 < 48; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_1024 float 1024
// i_x_384 float 384
// i_y_64 float 64
// i_x_128 float 128
// result float 768
void slow_performance(float *i_z_1024, float *i_x_384, float *i_y_64, float *i_x_128, float *result)
{
    float *tmp_1 = i_z_1024;
    float *tmp_2 = i_x_384;
    float tmp_3[32 * 12];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 12; k_3++)
        {
            tmp_3[i_3 * 12 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 12 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 12 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_64;
    float *tmp_5 = i_x_128;
    float tmp_6[8 * 16];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[48 * 16];
    for (int i_7 = 0; i_7 < 48; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 768; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_128 float 128
// i_x_1024 float 1024
// result float 128
void slow_performance(float *i_z_128, float *i_x_1024, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_x_1024;
    float tmp_3[8 * 64];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 64; k_3++)
        {
            tmp_3[i_3 * 64 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 64 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 64 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_1024;
    float tmp_5[8 * 16];
    for (int i_5 = 0; i_5 < 8; i_5++)
    {
        for (int k_5 = 0; k_5 < 16; k_5++)
        {
            tmp_5[i_5 * 16 + k_5] = 0;
            for (int j_5 = 0; j_5 < 64; j_5++)
            {
                tmp_5[i_5 * 16 + k_5] += tmp_3[i_5 * 64 + j_5] * tmp_4[j_5 * 16 + k_5];
            }
        }
    }
    for (int i_5 = 0; i_5 < 128; i_5++)
        result[i_5] = tmp_5[i_5];
}
/**********************************************************************************/
// i_x_192 float 192
// i_z_1024 float 1024
// result float 192
void slow_performance(float *i_x_192, float *i_z_1024, float *result)
{
    float *tmp_1 = i_x_192;
    float *tmp_2 = i_z_1024;
    float tmp_3[6 * 32];
    for (int i_3 = 0; i_3 < 6; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_192;
    float *tmp_5 = i_x_192;
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[24 * 8];
    for (int i_7 = 0; i_7 < 24; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_1024 float 1024
// i_y_64 float 64
// i_z_256 float 256
// result float 64
void slow_performance(float *i_x_1024, float *i_y_64, float *i_z_256, float *result)
{
    float *tmp_1 = i_x_1024;
    float *tmp_2 = i_y_64;
    float tmp_3[128 * 8];
    for (int i_3 = 0; i_3 < 128; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_256;
    float *tmp_5 = i_z_256;
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[32 * 2];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 2; k_7++)
        {
            tmp_7[i_7 * 2 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 2 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 2 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_768 float 768
// i_x_384 float 384
// i_x_256 float 256
// result float 512
void slow_performance(float *i_x_768, float *i_x_384, float *i_x_256, float *result)
{
    float *tmp_1 = i_x_768;
    float *tmp_2 = i_x_384;
    float tmp_3[16 * 8];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 48; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 48 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_256;
    float tmp_5[16 * 32];
    for (int i_5 = 0; i_5 < 16; i_5++)
    {
        for (int k_5 = 0; k_5 < 32; k_5++)
        {
            tmp_5[i_5 * 32 + k_5] = 0;
            for (int j_5 = 0; j_5 < 8; j_5++)
            {
                tmp_5[i_5 * 32 + k_5] += tmp_3[i_5 * 8 + j_5] * tmp_4[j_5 * 32 + k_5];
            }
        }
    }
    for (int i_5 = 0; i_5 < 512; i_5++)
        result[i_5] = tmp_5[i_5];
}
/**********************************************************************************/
// i_x_768 float 768
// i_z_192 float 192
// i_y_384 float 384
// result float 256
void slow_performance(float *i_x_768, float *i_z_192, float *i_y_384, float *result)
{
    float *tmp_1 = i_x_768;
    float *tmp_2 = i_z_192;
    float tmp_3[64 * 16];
    for (int i_3 = 0; i_3 < 64; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 12; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 12 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_y_384;
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 48; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 48 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[64 * 4];
    for (int i_7 = 0; i_7 < 64; i_7++)
    {
        for (int k_7 = 0; k_7 < 4; k_7++)
        {
            tmp_7[i_7 * 4 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 4 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 4 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_512 float 512
// i_z_64 float 64
// result float 1024
void slow_performance(float *i_y_512, float *i_z_64, float *result)
{
    float *tmp_1 = i_y_512;
    float tmp_2[1 * 512];
    for (int i_2 = 0; i_2 < 1; i_2++)
    {
        for (int j_2 = 0; j_2 < 512; j_2++)
        {
            tmp_2[j_2 * 1 + i_2] = tmp_1[i_2 * 512 + j_2];
        }
    }
    float *tmp_3 = i_z_64;
    float *tmp_4 = i_y_512;
    float tmp_5[8 * 64];
    for (int i_5 = 0; i_5 < 8; i_5++)
    {
        for (int k_5 = 0; k_5 < 64; k_5++)
        {
            tmp_5[i_5 * 64 + k_5] = 0;
            for (int j_5 = 0; j_5 < 8; j_5++)
            {
                tmp_5[i_5 * 64 + k_5] += tmp_3[i_5 * 8 + j_5] * tmp_4[j_5 * 64 + k_5];
            }
        }
    }
    float tmp_6[32 * 32];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_2[i_6 * 16 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 1024; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_128 float 128
// i_y_64 float 64
// i_z_384 float 384
// i_z_768 float 768
// result float 1024
void slow_performance(float *i_z_128, float *i_y_64, float *i_z_384, float *i_z_768, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_y_64;
    float tmp_3[32 * 16];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 4; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 4 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_384;
    float *tmp_5 = i_z_768;
    float tmp_6[16 * 32];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[32 * 32];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_1024 float 1024
// result float 64
void slow_performance(float *i_y_1024, float *result)
{
    float *tmp_1 = i_y_1024;
    float *tmp_2 = i_y_1024;
    float tmp_3[64 * 16];
    for (int i_3 = 0; i_3 < 64; i_3++)
    {
        for (int j_3 = 0; j_3 < 16; j_3++)
        {
            tmp_3[j_3 * 64 + i_3] = tmp_2[i_3 * 16 + j_3];
        }
    }
    float tmp_4[8 * 8];
    for (int i_4 = 0; i_4 < 8; i_4++)
    {
        for (int k_4 = 0; k_4 < 8; k_4++)
        {
            tmp_4[i_4 * 8 + k_4] = 0;
            for (int j_4 = 0; j_4 < 128; j_4++)
            {
                tmp_4[i_4 * 8 + k_4] += tmp_1[i_4 * 128 + j_4] * tmp_3[j_4 * 8 + k_4];
            }
        }
    }
    for (int i_4 = 0; i_4 < 64; i_4++)
        result[i_4] = tmp_4[i_4];
}
/**********************************************************************************/
// i_x_256 float 256
// i_z_768 float 768
// i_y_384 float 384
// i_z_192 float 192
// result float 384
void slow_performance(float *i_x_256, float *i_z_768, float *i_y_384, float *i_z_192, float *result)
{
    float *tmp_1 = i_x_256;
    float *tmp_2 = i_z_768;
    float tmp_3[8 * 24];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 24; k_3++)
        {
            tmp_3[i_3 * 24 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 24 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 24 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_z_192;
    float tmp_6[32 * 16];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 12; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 12 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[12 * 32];
    for (int i_7 = 0; i_7 < 12; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_512 float 512
// i_x_256 float 256
// i_z_384 float 384
// i_z_128 float 128
// result float 384
void slow_performance(float *i_y_512, float *i_x_256, float *i_z_384, float *i_z_128, float *result)
{
    float *tmp_1 = i_y_512;
    float *tmp_2 = i_x_256;
    float tmp_3[16 * 8];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_384;
    float *tmp_5 = i_z_128;
    float tmp_6[24 * 8];
    for (int i_6 = 0; i_6 < 24; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[16 * 24];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 24; k_7++)
        {
            tmp_7[i_7 * 24 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 24 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 24 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_768 float 768
// i_z_384 float 384
// result float 192
void slow_performance(float *i_x_768, float *i_z_384, float *result)
{
    float *tmp_1 = i_x_768;
    float tmp_2[12 * 64];
    for (int i_2 = 0; i_2 < 12; i_2++)
    {
        for (int j_2 = 0; j_2 < 64; j_2++)
        {
            tmp_2[j_2 * 12 + i_2] = tmp_1[i_2 * 64 + j_2];
        }
    }
    float *tmp_3 = i_z_384;
    float *tmp_4 = i_z_384;
    float tmp_5[32 * 32];
    for (int i_5 = 0; i_5 < 32; i_5++)
    {
        for (int k_5 = 0; k_5 < 32; k_5++)
        {
            tmp_5[i_5 * 32 + k_5] = 0;
            for (int j_5 = 0; j_5 < 12; j_5++)
            {
                tmp_5[i_5 * 32 + k_5] += tmp_3[i_5 * 12 + j_5] * tmp_4[j_5 * 32 + k_5];
            }
        }
    }
    float tmp_6[12 * 16];
    for (int i_6 = 0; i_6 < 12; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 64; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_2[i_6 * 64 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 192; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_64 float 64
// i_x_256 float 256
// i_y_384 float 384
// result float 384
void slow_performance(float *i_z_64, float *i_x_256, float *i_y_384, float *result)
{
    float *tmp_1 = i_z_64;
    float *tmp_2 = i_x_256;
    float tmp_3[8 * 32];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_256;
    float *tmp_5 = i_y_384;
    float tmp_6[16 * 24];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 24; k_6++)
        {
            tmp_6[i_6 * 24 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 24 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 24 + k_6];
            }
        }
    }
    float tmp_7[16 * 24];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 24; k_7++)
        {
            tmp_7[i_7 * 24 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 24 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 24 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_192 float 192
// i_y_384 float 384
// i_z_256 float 256
// i_x_128 float 128
// result float 64
void slow_performance(float *i_y_192, float *i_y_384, float *i_z_256, float *i_x_128, float *result)
{
    float *tmp_1 = i_y_192;
    float *tmp_2 = i_y_384;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 12; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 12 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_256;
    float *tmp_5 = i_x_128;
    float tmp_6[16 * 8];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[16 * 4];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 4; k_7++)
        {
            tmp_7[i_7 * 4 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 4 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 4 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_512 float 512
// i_y_128 float 128
// i_y_1024 float 1024
// result float 128
void slow_performance(float *i_z_512, float *i_y_128, float *i_y_1024, float *result)
{
    float *tmp_1 = i_z_512;
    float *tmp_2 = i_y_128;
    float tmp_3[16 * 4];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_128;
    float *tmp_5 = i_y_1024;
    float tmp_6[8 * 64];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 64; k_6++)
        {
            tmp_6[i_6 * 64 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 64 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 64 + k_6];
            }
        }
    }
    float tmp_7[4 * 32];
    for (int i_7 = 0; i_7 < 4; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_1024 float 1024
// i_y_384 float 384
// i_z_192 float 192
// i_x_768 float 768
// result float 384
void slow_performance(float *i_x_1024, float *i_y_384, float *i_z_192, float *i_x_768, float *result)
{
    float *tmp_1 = i_x_1024;
    float *tmp_2 = i_y_384;
    float tmp_3[32 * 12];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 12; k_3++)
        {
            tmp_3[i_3 * 12 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 12 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 12 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_192;
    float *tmp_5 = i_x_768;
    float tmp_6[4 * 16];
    for (int i_6 = 0; i_6 < 4; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 48; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 48 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[48 * 8];
    for (int i_7 = 0; i_7 < 48; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_512 float 512
// i_x_128 float 128
// i_z_1024 float 1024
// result float 128
void slow_performance(float *i_x_512, float *i_x_128, float *i_z_1024, float *result)
{
    float *tmp_1 = i_x_512;
    float *tmp_2 = i_x_128;
    float tmp_3[32 * 8];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_1024;
    float *tmp_5 = i_x_128;
    float tmp_6[32 * 4];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 4; k_6++)
        {
            tmp_6[i_6 * 4 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 4 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 4 + k_6];
            }
        }
    }
    float tmp_7[16 * 8];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_256 float 256
// i_y_384 float 384
// i_z_512 float 512
// result float 768
void slow_performance(float *i_y_256, float *i_y_384, float *i_z_512, float *result)
{
    float *tmp_1 = i_y_256;
    float *tmp_2 = i_y_384;
    float tmp_3[16 * 24];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 24; k_3++)
        {
            tmp_3[i_3 * 24 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 24 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 24 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_256;
    float *tmp_5 = i_z_512;
    float tmp_6[16 * 32];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[24 * 32];
    for (int i_7 = 0; i_7 < 24; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 768; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_768 float 768
// i_z_256 float 256
// result float 64
void slow_performance(float *i_x_768, float *i_z_256, float *result)
{
    float *tmp_1 = i_x_768;
    float *tmp_2 = i_x_768;
    float tmp_3[16 * 16];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 48; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 48 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_256;
    float *tmp_5 = i_z_256;
    float tmp_6[2 * 128];
    for (int i_6 = 0; i_6 < 2; i_6++)
    {
        for (int j_6 = 0; j_6 < 128; j_6++)
        {
            tmp_6[i_6 * 128 + j_6] = tmp_4[i_6 * 128 + j_6] + tmp_5[i_6 * 128 + j_6];
        }
    }
    float tmp_7[8 * 8];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_1024 float 1024
// i_z_128 float 128
// i_x_192 float 192
// i_x_384 float 384
// result float 1024
void slow_performance(float *i_z_1024, float *i_z_128, float *i_x_192, float *i_x_384, float *result)
{
    float *tmp_1 = i_z_1024;
    float *tmp_2 = i_z_128;
    float tmp_3[32 * 4];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_192;
    float *tmp_5 = i_x_384;
    float tmp_6[16 * 32];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 12; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 12 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[16 * 64];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_64 float 64
// i_y_1024 float 1024
// i_x_256 float 256
// result float 64
void slow_performance(float *i_y_64, float *i_y_1024, float *i_x_256, float *result)
{
    float *tmp_1 = i_y_64;
    float tmp_2[4 * 16];
    for (int i_2 = 0; i_2 < 4; i_2++)
    {
        for (int j_2 = 0; j_2 < 16; j_2++)
        {
            tmp_2[j_2 * 4 + i_2] = tmp_1[i_2 * 16 + j_2];
        }
    }
    float *tmp_3 = i_y_1024;
    float *tmp_4 = i_x_256;
    float tmp_5[16 * 4];
    for (int i_5 = 0; i_5 < 16; i_5++)
    {
        for (int k_5 = 0; k_5 < 4; k_5++)
        {
            tmp_5[i_5 * 4 + k_5] = 0;
            for (int j_5 = 0; j_5 < 64; j_5++)
            {
                tmp_5[i_5 * 4 + k_5] += tmp_3[i_5 * 64 + j_5] * tmp_4[j_5 * 4 + k_5];
            }
        }
    }
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int j_6 = 0; j_6 < 8; j_6++)
        {
            tmp_6[i_6 * 8 + j_6] = tmp_2[i_6 * 8 + j_6] + tmp_5[i_6 * 8 + j_6];
        }
    }
    for (int i_6 = 0; i_6 < 64; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_y_256 float 256
// i_x_1024 float 1024
// i_y_768 float 768
// result float 192
void slow_performance(float *i_y_256, float *i_x_1024, float *i_y_768, float *result)
{
    float *tmp_1 = i_y_256;
    float tmp_2[256 * 1];
    for (int i_2 = 0; i_2 < 256; i_2++)
    {
        for (int j_2 = 0; j_2 < 1; j_2++)
        {
            tmp_2[j_2 * 256 + i_2] = tmp_1[i_2 * 1 + j_2];
        }
    }
    float *tmp_3 = i_x_1024;
    float *tmp_4 = i_y_768;
    float tmp_5[16 * 12];
    for (int i_5 = 0; i_5 < 16; i_5++)
    {
        for (int k_5 = 0; k_5 < 12; k_5++)
        {
            tmp_5[i_5 * 12 + k_5] = 0;
            for (int j_5 = 0; j_5 < 64; j_5++)
            {
                tmp_5[i_5 * 12 + k_5] += tmp_3[i_5 * 64 + j_5] * tmp_4[j_5 * 12 + k_5];
            }
        }
    }
    float tmp_6[16 * 12];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 12; k_6++)
        {
            tmp_6[i_6 * 12 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 12 + k_6] += tmp_2[i_6 * 16 + j_6] * tmp_5[j_6 * 12 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 192; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_512 float 512
// i_y_256 float 256
// result float 128
void slow_performance(float *i_z_512, float *i_y_256, float *result)
{
    float *tmp_1 = i_z_512;
    float *tmp_2 = i_y_256;
    float tmp_3[16 * 8];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float tmp_4[4 * 32];
    for (int i_4 = 0; i_4 < 4; i_4++)
    {
        for (int j_4 = 0; j_4 < 32; j_4++)
        {
            tmp_4[j_4 * 4 + i_4] = tmp_3[i_4 * 32 + j_4];
        }
    }
    for (int i_4 = 0; i_4 < 128; i_4++)
        result[i_4] = tmp_4[i_4];
}
/**********************************************************************************/
// i_y_384 float 384
// i_z_64 float 64
// result float 256
void slow_performance(float *i_y_384, float *i_z_64, float *result)
{
    float *tmp_1 = i_y_384;
    float *tmp_2 = i_z_64;
    float tmp_3[48 * 8];
    for (int i_3 = 0; i_3 < 48; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_z_64;
    float tmp_6[48 * 8];
    for (int i_6 = 0; i_6 < 48; i_6++)
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
    float tmp_7[16 * 16];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 24; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 24 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_1024 float 1024
// i_x_192 float 192
// i_y_768 float 768
// result float 1024
void slow_performance(float *i_y_1024, float *i_x_192, float *i_y_768, float *result)
{
    float *tmp_1 = i_y_1024;
    float *tmp_2 = i_x_192;
    float *tmp_3 = i_y_768;
    float tmp_4[4 * 16];
    for (int i_4 = 0; i_4 < 4; i_4++)
    {
        for (int k_4 = 0; k_4 < 16; k_4++)
        {
            tmp_4[i_4 * 16 + k_4] = 0;
            for (int j_4 = 0; j_4 < 48; j_4++)
            {
                tmp_4[i_4 * 16 + k_4] += tmp_2[i_4 * 48 + j_4] * tmp_3[j_4 * 16 + k_4];
            }
        }
    }
    float tmp_5[128 * 8];
    for (int i_5 = 0; i_5 < 128; i_5++)
    {
        for (int k_5 = 0; k_5 < 8; k_5++)
        {
            tmp_5[i_5 * 8 + k_5] = 0;
            for (int j_5 = 0; j_5 < 8; j_5++)
            {
                tmp_5[i_5 * 8 + k_5] += tmp_1[i_5 * 8 + j_5] * tmp_4[j_5 * 8 + k_5];
            }
        }
    }
    for (int i_5 = 0; i_5 < 1024; i_5++)
        result[i_5] = tmp_5[i_5];
}
/**********************************************************************************/
// i_y_384 float 384
// i_x_1024 float 1024
// i_y_128 float 128
// result float 768
void slow_performance(float *i_y_384, float *i_x_1024, float *i_y_128, float *result)
{
    float *tmp_1 = i_y_384;
    float *tmp_2 = i_x_1024;
    float *tmp_3 = i_y_128;
    float tmp_4[32 * 4];
    for (int i_4 = 0; i_4 < 32; i_4++)
    {
        for (int k_4 = 0; k_4 < 4; k_4++)
        {
            tmp_4[i_4 * 4 + k_4] = 0;
            for (int j_4 = 0; j_4 < 32; j_4++)
            {
                tmp_4[i_4 * 4 + k_4] += tmp_2[i_4 * 32 + j_4] * tmp_3[j_4 * 4 + k_4];
            }
        }
    }
    float tmp_5[48 * 16];
    for (int i_5 = 0; i_5 < 48; i_5++)
    {
        for (int k_5 = 0; k_5 < 16; k_5++)
        {
            tmp_5[i_5 * 16 + k_5] = 0;
            for (int j_5 = 0; j_5 < 8; j_5++)
            {
                tmp_5[i_5 * 16 + k_5] += tmp_1[i_5 * 8 + j_5] * tmp_4[j_5 * 16 + k_5];
            }
        }
    }
    for (int i_5 = 0; i_5 < 768; i_5++)
        result[i_5] = tmp_5[i_5];
}
/**********************************************************************************/
// i_x_256 float 256
// i_y_192 float 192
// result float 192
void slow_performance(float *i_x_256, float *i_y_192, float *result)
{
    float *tmp_1 = i_x_256;
    float *tmp_2 = i_x_256;
    float tmp_3[32 * 32];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_192;
    float *tmp_5 = i_x_256;
    float tmp_6[12 * 16];
    for (int i_6 = 0; i_6 < 12; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[32 * 6];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 6; k_7++)
        {
            tmp_7[i_7 * 6 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 6 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 6 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_256 float 256
// i_x_128 float 128
// i_x_64 float 64
// result float 512
void slow_performance(float *i_z_256, float *i_x_128, float *i_x_64, float *result)
{
    float *tmp_1 = i_z_256;
    float *tmp_2 = i_x_128;
    float tmp_3[32 * 16];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_64;
    float *tmp_5 = i_z_256;
    float tmp_6[4 * 16];
    for (int i_6 = 0; i_6 < 4; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[64 * 8];
    for (int i_7 = 0; i_7 < 64; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_128 float 128
// i_x_256 float 256
// i_z_1024 float 1024
// result float 512
void slow_performance(float *i_y_128, float *i_x_256, float *i_z_1024, float *result)
{
    float *tmp_1 = i_y_128;
    float *tmp_2 = i_x_256;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_1024;
    float *tmp_5 = i_z_1024;
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 128; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 128 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[64 * 8];
    for (int i_7 = 0; i_7 < 64; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_1024 float 1024
// i_z_768 float 768
// i_x_192 float 192
// result float 64
void slow_performance(float *i_x_1024, float *i_z_768, float *i_x_192, float *result)
{
    float *tmp_1 = i_x_1024;
    float *tmp_2 = i_z_768;
    float *tmp_3 = i_x_192;
    float tmp_4[16 * 4];
    for (int i_4 = 0; i_4 < 16; i_4++)
    {
        for (int k_4 = 0; k_4 < 4; k_4++)
        {
            tmp_4[i_4 * 4 + k_4] = 0;
            for (int j_4 = 0; j_4 < 48; j_4++)
            {
                tmp_4[i_4 * 4 + k_4] += tmp_2[i_4 * 48 + j_4] * tmp_3[j_4 * 4 + k_4];
            }
        }
    }
    float tmp_5[32 * 2];
    for (int i_5 = 0; i_5 < 32; i_5++)
    {
        for (int k_5 = 0; k_5 < 2; k_5++)
        {
            tmp_5[i_5 * 2 + k_5] = 0;
            for (int j_5 = 0; j_5 < 32; j_5++)
            {
                tmp_5[i_5 * 2 + k_5] += tmp_1[i_5 * 32 + j_5] * tmp_4[j_5 * 2 + k_5];
            }
        }
    }
    for (int i_5 = 0; i_5 < 64; i_5++)
        result[i_5] = tmp_5[i_5];
}
/**********************************************************************************/
// i_z_256 float 256
// i_y_1024 float 1024
// i_x_128 float 128
// result float 128
void slow_performance(float *i_z_256, float *i_y_1024, float *i_x_128, float *result)
{
    float *tmp_1 = i_z_256;
    float *tmp_2 = i_y_1024;
    float tmp_3[16 * 64];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 64; k_3++)
        {
            tmp_3[i_3 * 64 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 64 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 64 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_128;
    float *tmp_5 = i_y_1024;
    float tmp_6[8 * 64];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 64; k_6++)
        {
            tmp_6[i_6 * 64 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 64 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 64 + k_6];
            }
        }
    }
    float tmp_7[16 * 8];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 64; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 64 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_256 float 256
// i_y_64 float 64
// i_y_128 float 128
// result float 128
void slow_performance(float *i_x_256, float *i_y_64, float *i_y_128, float *result)
{
    float *tmp_1 = i_x_256;
    float *tmp_2 = i_y_64;
    float tmp_3[64 * 16];
    for (int i_3 = 0; i_3 < 64; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 4; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 4 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_128;
    float tmp_5[4 * 32];
    for (int i_5 = 0; i_5 < 4; i_5++)
    {
        for (int j_5 = 0; j_5 < 32; j_5++)
        {
            tmp_5[j_5 * 4 + i_5] = tmp_4[i_5 * 32 + j_5];
        }
    }
    float tmp_6[32 * 4];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 4; k_6++)
        {
            tmp_6[i_6 * 4 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 4 + k_6] += tmp_3[i_6 * 32 + j_6] * tmp_5[j_6 * 4 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 128; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_768 float 768
// i_y_512 float 512
// i_y_64 float 64
// i_y_128 float 128
// result float 768
void slow_performance(float *i_z_768, float *i_y_512, float *i_y_64, float *i_y_128, float *result)
{
    float *tmp_1 = i_z_768;
    float *tmp_2 = i_y_512;
    float tmp_3[24 * 16];
    for (int i_3 = 0; i_3 < 24; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_64;
    float *tmp_5 = i_y_128;
    float tmp_6[8 * 16];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[48 * 16];
    for (int i_7 = 0; i_7 < 48; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 768; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_768 float 768
// i_z_256 float 256
// result float 768
void slow_performance(float *i_x_768, float *i_z_256, float *result)
{
    float *tmp_1 = i_x_768;
    float tmp_2[768 * 1];
    for (int i_2 = 0; i_2 < 768; i_2++)
    {
        for (int j_2 = 0; j_2 < 1; j_2++)
        {
            tmp_2[j_2 * 768 + i_2] = tmp_1[i_2 * 1 + j_2];
        }
    }
    float *tmp_3 = i_z_256;
    float tmp_4[48 * 16];
    for (int i_4 = 0; i_4 < 48; i_4++)
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
    for (int i_4 = 0; i_4 < 768; i_4++)
        result[i_4] = tmp_4[i_4];
}
/**********************************************************************************/
// i_z_512 float 512
// i_z_1024 float 1024
// i_y_384 float 384
// result float 512
void slow_performance(float *i_z_512, float *i_z_1024, float *i_y_384, float *result)
{
    float *tmp_1 = i_z_512;
    float *tmp_2 = i_z_1024;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_y_384;
    float tmp_6[32 * 32];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 12; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 12 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[16 * 32];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_128 float 128
// i_y_64 float 64
// i_z_256 float 256
// result float 128
void slow_performance(float *i_x_128, float *i_y_64, float *i_z_256, float *result)
{
    float *tmp_1 = i_x_128;
    float *tmp_2 = i_y_64;
    float tmp_3[16 * 8];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_256;
    float tmp_5[64 * 4];
    for (int i_5 = 0; i_5 < 64; i_5++)
    {
        for (int j_5 = 0; j_5 < 4; j_5++)
        {
            tmp_5[j_5 * 64 + i_5] = tmp_4[i_5 * 4 + j_5];
        }
    }
    float tmp_6[8 * 16];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_3[i_6 * 16 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 128; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_192 float 192
// i_y_1024 float 1024
// result float 768
void slow_performance(float *i_z_192, float *i_y_1024, float *result)
{
    float *tmp_1 = i_z_192;
    float tmp_2[64 * 3];
    for (int i_2 = 0; i_2 < 64; i_2++)
    {
        for (int j_2 = 0; j_2 < 3; j_2++)
        {
            tmp_2[j_2 * 64 + i_2] = tmp_1[i_2 * 3 + j_2];
        }
    }
    float *tmp_3 = i_y_1024;
    float *tmp_4 = i_y_1024;
    float tmp_5[8 * 8];
    for (int i_5 = 0; i_5 < 8; i_5++)
    {
        for (int k_5 = 0; k_5 < 8; k_5++)
        {
            tmp_5[i_5 * 8 + k_5] = 0;
            for (int j_5 = 0; j_5 < 128; j_5++)
            {
                tmp_5[i_5 * 8 + k_5] += tmp_3[i_5 * 128 + j_5] * tmp_4[j_5 * 8 + k_5];
            }
        }
    }
    float tmp_6[48 * 16];
    for (int i_6 = 0; i_6 < 48; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 4; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_2[i_6 * 4 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 768; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_64 float 64
// i_y_768 float 768
// result float 256
void slow_performance(float *i_z_64, float *i_y_768, float *result)
{
    float *tmp_1 = i_z_64;
    float *tmp_2 = i_z_64;
    float tmp_3[16 * 16];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 4; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 4 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_768;
    float *tmp_5 = i_y_768;
    float tmp_6[16 * 16];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 48; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 48 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[8 * 32];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int j_7 = 0; j_7 < 32; j_7++)
        {
            tmp_7[i_7 * 32 + j_7] = tmp_3[i_7 * 32 + j_7] + tmp_6[i_7 * 32 + j_7];
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_512 float 512
// i_z_128 float 128
// result float 512
void slow_performance(float *i_x_512, float *i_z_128, float *result)
{
    float *tmp_1 = i_x_512;
    float *tmp_2 = i_x_512;
    float tmp_3[2 * 256];
    for (int i_3 = 0; i_3 < 2; i_3++)
    {
        for (int j_3 = 0; j_3 < 256; j_3++)
        {
            tmp_3[i_3 * 256 + j_3] = tmp_1[i_3 * 256 + j_3] + tmp_2[i_3 * 256 + j_3];
        }
    }
    float *tmp_4 = i_z_128;
    float *tmp_5 = i_z_128;
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[64 * 8];
    for (int i_7 = 0; i_7 < 64; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_256 float 256
// i_x_64 float 64
// i_y_768 float 768
// i_z_192 float 192
// result float 64
void slow_performance(float *i_y_256, float *i_x_64, float *i_y_768, float *i_z_192, float *result)
{
    float *tmp_1 = i_y_256;
    float *tmp_2 = i_x_64;
    float tmp_3[32 * 8];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_768;
    float *tmp_5 = i_z_192;
    float tmp_6[32 * 8];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[8 * 8];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_512 float 512
// i_x_256 float 256
// i_z_1024 float 1024
// i_z_64 float 64
// result float 512
void slow_performance(float *i_z_512, float *i_x_256, float *i_z_1024, float *i_z_64, float *result)
{
    float *tmp_1 = i_z_512;
    float *tmp_2 = i_x_256;
    float tmp_3[32 * 16];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_1024;
    float *tmp_5 = i_z_64;
    float tmp_6[32 * 2];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 2; k_6++)
        {
            tmp_6[i_6 * 2 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 2 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 2 + k_6];
            }
        }
    }
    float tmp_7[64 * 8];
    for (int i_7 = 0; i_7 < 64; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_384 float 384
// i_x_768 float 768
// i_x_128 float 128
// result float 512
void slow_performance(float *i_z_384, float *i_x_768, float *i_x_128, float *result)
{
    float *tmp_1 = i_z_384;
    float *tmp_2 = i_x_768;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 24; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 24 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_128;
    float *tmp_5 = i_x_128;
    float tmp_6[8 * 8];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[64 * 8];
    for (int i_7 = 0; i_7 < 64; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_64 float 64
// i_z_1024 float 1024
// i_x_768 float 768
// i_y_192 float 192
// result float 1024
void slow_performance(float *i_y_64, float *i_z_1024, float *i_x_768, float *i_y_192, float *result)
{
    float *tmp_1 = i_y_64;
    float *tmp_2 = i_z_1024;
    float tmp_3[8 * 128];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 128; k_3++)
        {
            tmp_3[i_3 * 128 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 128 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 128 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_768;
    float *tmp_5 = i_y_192;
    float tmp_6[32 * 8];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[64 * 16];
    for (int i_7 = 0; i_7 < 64; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_256 float 256
// i_x_64 float 64
// i_z_768 float 768
// i_x_192 float 192
// result float 1024
void slow_performance(float *i_x_256, float *i_x_64, float *i_z_768, float *i_x_192, float *result)
{
    float *tmp_1 = i_x_256;
    float *tmp_2 = i_x_64;
    float tmp_3[16 * 4];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_768;
    float *tmp_5 = i_x_192;
    float tmp_6[64 * 16];
    for (int i_6 = 0; i_6 < 64; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 12; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 12 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[8 * 128];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 128; k_7++)
        {
            tmp_7[i_7 * 128 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 128 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 128 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_768 float 768
// i_y_192 float 192
// i_z_64 float 64
// result float 64
void slow_performance(float *i_y_768, float *i_y_192, float *i_z_64, float *result)
{
    float *tmp_1 = i_y_768;
    float *tmp_2 = i_y_192;
    float tmp_3[16 * 4];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 48; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 48 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_64;
    float *tmp_5 = i_z_64;
    float tmp_6[32 * 32];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 2; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 2 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[2 * 32];
    for (int i_7 = 0; i_7 < 2; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_128 float 128
// i_y_1024 float 1024
// i_z_768 float 768
// result float 128
void slow_performance(float *i_z_128, float *i_y_1024, float *i_z_768, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_y_1024;
    float tmp_3[4 * 32];
    for (int i_3 = 0; i_3 < 4; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_768;
    float *tmp_5 = i_z_768;
    float tmp_6[16 * 16];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 48; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 48 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[8 * 16];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_256 float 256
// i_y_1024 float 1024
// i_x_512 float 512
// i_y_128 float 128
// result float 1024
void slow_performance(float *i_x_256, float *i_y_1024, float *i_x_512, float *i_y_128, float *result)
{
    float *tmp_1 = i_x_256;
    float *tmp_2 = i_y_1024;
    float tmp_3[8 * 32];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_512;
    float *tmp_5 = i_y_128;
    float tmp_6[32 * 8];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[32 * 32];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_64 float 64
// i_z_192 float 192
// i_x_384 float 384
// result float 512
void slow_performance(float *i_x_64, float *i_z_192, float *i_x_384, float *result)
{
    float *tmp_1 = i_x_64;
    float tmp_2[16 * 4];
    for (int i_2 = 0; i_2 < 16; i_2++)
    {
        for (int j_2 = 0; j_2 < 4; j_2++)
        {
            tmp_2[j_2 * 16 + i_2] = tmp_1[i_2 * 4 + j_2];
        }
    }
    float *tmp_3 = i_z_192;
    float *tmp_4 = i_x_384;
    float tmp_5[8 * 16];
    for (int i_5 = 0; i_5 < 8; i_5++)
    {
        for (int k_5 = 0; k_5 < 16; k_5++)
        {
            tmp_5[i_5 * 16 + k_5] = 0;
            for (int j_5 = 0; j_5 < 24; j_5++)
            {
                tmp_5[i_5 * 16 + k_5] += tmp_3[i_5 * 24 + j_5] * tmp_4[j_5 * 16 + k_5];
            }
        }
    }
    float tmp_6[16 * 32];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 4; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_2[i_6 * 4 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 512; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_x_256 float 256
// i_y_512 float 512
// i_x_384 float 384
// result float 768
void slow_performance(float *i_x_256, float *i_y_512, float *i_x_384, float *result)
{
    float *tmp_1 = i_x_256;
    float *tmp_2 = i_y_512;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_384;
    float tmp_5[96 * 4];
    for (int i_5 = 0; i_5 < 96; i_5++)
    {
        for (int j_5 = 0; j_5 < 4; j_5++)
        {
            tmp_5[j_5 * 96 + i_5] = tmp_4[i_5 * 4 + j_5];
        }
    }
    float tmp_6[32 * 24];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 24; k_6++)
        {
            tmp_6[i_6 * 24 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 24 + k_6] += tmp_3[i_6 * 16 + j_6] * tmp_5[j_6 * 24 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 768; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_128 float 128
// i_y_256 float 256
// result float 256
void slow_performance(float *i_z_128, float *i_y_256, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_y_256;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_128;
    float *tmp_5 = i_y_256;
    float tmp_6[16 * 32];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[16 * 16];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_768 float 768
// i_z_64 float 64
// i_x_1024 float 1024
// result float 256
void slow_performance(float *i_x_768, float *i_z_64, float *i_x_1024, float *result)
{
    float *tmp_1 = i_x_768;
    float *tmp_2 = i_x_768;
    float tmp_3[16 * 16];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 48; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 48 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_64;
    float *tmp_5 = i_x_1024;
    float tmp_6[2 * 32];
    for (int i_6 = 0; i_6 < 2; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[32 * 8];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_1024 float 1024
// i_x_64 float 64
// i_x_192 float 192
// i_x_768 float 768
// result float 256
void slow_performance(float *i_y_1024, float *i_x_64, float *i_x_192, float *i_x_768, float *result)
{
    float *tmp_1 = i_y_1024;
    float *tmp_2 = i_x_64;
    float tmp_3[128 * 8];
    for (int i_3 = 0; i_3 < 128; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_192;
    float *tmp_5 = i_x_768;
    float tmp_6[8 * 32];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[32 * 8];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_1024 float 1024
// i_y_128 float 128
// i_y_192 float 192
// result float 128
void slow_performance(float *i_x_1024, float *i_y_128, float *i_y_192, float *result)
{
    float *tmp_1 = i_x_1024;
    float *tmp_2 = i_y_128;
    float tmp_3[32 * 4];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 4; k_3++)
        {
            tmp_3[i_3 * 4 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 4 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_192;
    float *tmp_5 = i_y_192;
    float tmp_6[32 * 32];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 6; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 6 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[4 * 32];
    for (int i_7 = 0; i_7 < 4; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_192 float 192
// i_y_384 float 384
// i_z_1024 float 1024
// result float 384
void slow_performance(float *i_y_192, float *i_y_384, float *i_z_1024, float *result)
{
    float *tmp_1 = i_y_192;
    float *tmp_2 = i_y_192;
    float tmp_3[8 * 8];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 24; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 24 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_384;
    float *tmp_5 = i_z_1024;
    float tmp_6[12 * 32];
    for (int i_6 = 0; i_6 < 12; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[8 * 48];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 48; k_7++)
        {
            tmp_7[i_7 * 48 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 48 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 48 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_128 float 128
// i_y_384 float 384
// i_z_512 float 512
// i_z_192 float 192
// result float 512
void slow_performance(float *i_z_128, float *i_y_384, float *i_z_512, float *i_z_192, float *result)
{
    float *tmp_1 = i_z_128;
    float *tmp_2 = i_y_384;
    float tmp_3[8 * 24];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 24; k_3++)
        {
            tmp_3[i_3 * 24 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 24 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 24 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_512;
    float *tmp_5 = i_z_192;
    float tmp_6[32 * 12];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 12; k_6++)
        {
            tmp_6[i_6 * 12 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 12 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 12 + k_6];
            }
        }
    }
    float tmp_7[16 * 32];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 12; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 12 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_512 float 512
// i_z_256 float 256
// i_x_128 float 128
// result float 128
void slow_performance(float *i_y_512, float *i_z_256, float *i_x_128, float *result)
{
    float *tmp_1 = i_y_512;
    float *tmp_2 = i_y_512;
    float tmp_3[16 * 16];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_256;
    float *tmp_5 = i_x_128;
    float tmp_6[16 * 8];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 8; k_6++)
        {
            tmp_6[i_6 * 8 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];
            }
        }
    }
    float tmp_7[16 * 8];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 128; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_384 float 384
// i_y_1024 float 1024
// i_y_128 float 128
// result float 768
void slow_performance(float *i_y_384, float *i_y_1024, float *i_y_128, float *result)
{
    float *tmp_1 = i_y_384;
    float tmp_2[96 * 4];
    for (int i_2 = 0; i_2 < 96; i_2++)
    {
        for (int j_2 = 0; j_2 < 4; j_2++)
        {
            tmp_2[j_2 * 96 + i_2] = tmp_1[i_2 * 4 + j_2];
        }
    }
    float *tmp_3 = i_y_1024;
    float *tmp_4 = i_y_128;
    float tmp_5[64 * 8];
    for (int i_5 = 0; i_5 < 64; i_5++)
    {
        for (int k_5 = 0; k_5 < 8; k_5++)
        {
            tmp_5[i_5 * 8 + k_5] = 0;
            for (int j_5 = 0; j_5 < 16; j_5++)
            {
                tmp_5[i_5 * 8 + k_5] += tmp_3[i_5 * 16 + j_5] * tmp_4[j_5 * 8 + k_5];
            }
        }
    }
    float tmp_6[24 * 32];
    for (int i_6 = 0; i_6 < 24; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_2[i_6 * 16 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    for (int i_6 = 0; i_6 < 768; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_z_192 float 192
// i_x_64 float 64
// i_z_256 float 256
// i_z_768 float 768
// result float 256
void slow_performance(float *i_z_192, float *i_x_64, float *i_z_256, float *i_z_768, float *result)
{
    float *tmp_1 = i_z_192;
    float *tmp_2 = i_x_64;
    float tmp_3[48 * 16];
    for (int i_3 = 0; i_3 < 48; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 4; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 4 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_256;
    float *tmp_5 = i_z_768;
    float tmp_6[8 * 24];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 24; k_6++)
        {
            tmp_6[i_6 * 24 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 24 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 24 + k_6];
            }
        }
    }
    float tmp_7[32 * 8];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 24; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 24 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 256; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_256 float 256
// i_z_384 float 384
// i_y_64 float 64
// result float 384
void slow_performance(float *i_y_256, float *i_z_384, float *i_y_64, float *result)
{
    float *tmp_1 = i_y_256;
    float *tmp_2 = i_y_256;
    float tmp_3[32 * 32];
    for (int i_3 = 0; i_3 < 32; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_384;
    float *tmp_5 = i_y_64;
    float tmp_6[48 * 8];
    for (int i_6 = 0; i_6 < 48; i_6++)
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
    float tmp_7[32 * 12];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 12; k_7++)
        {
            tmp_7[i_7 * 12 + k_7] = 0;
            for (int j_7 = 0; j_7 < 32; j_7++)
            {
                tmp_7[i_7 * 12 + k_7] += tmp_3[i_7 * 32 + j_7] * tmp_6[j_7 * 12 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 384; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_64 float 64
// i_y_1024 float 1024
// i_y_192 float 192
// i_z_384 float 384
// result float 512
void slow_performance(float *i_z_64, float *i_y_1024, float *i_y_192, float *i_z_384, float *result)
{
    float *tmp_1 = i_z_64;
    float *tmp_2 = i_y_1024;
    float tmp_3[2 * 32];
    for (int i_3 = 0; i_3 < 2; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_192;
    float *tmp_5 = i_z_384;
    float tmp_6[16 * 32];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 12; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 12 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[8 * 64];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_192 float 192
// i_x_64 float 64
// i_z_256 float 256
// result float 192
void slow_performance(float *i_y_192, float *i_x_64, float *i_z_256, float *result)
{
    float *tmp_1 = i_y_192;
    float *tmp_2 = i_x_64;
    float tmp_3[24 * 8];
    for (int i_3 = 0; i_3 < 24; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 8; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_192;
    float *tmp_5 = i_z_256;
    float tmp_6[12 * 16];
    for (int i_6 = 0; i_6 < 12; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[192 * 1];
    for (int i_7 = 0; i_7 < 192; i_7++)
    {
        for (int j_7 = 0; j_7 < 1; j_7++)
        {
            tmp_7[i_7 * 1 + j_7] = tmp_3[i_7 * 1 + j_7] + tmp_6[i_7 * 1 + j_7];
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_768 float 768
// i_y_1024 float 1024
// i_x_128 float 128
// i_z_512 float 512
// result float 768
void slow_performance(float *i_y_768, float *i_y_1024, float *i_x_128, float *i_z_512, float *result)
{
    float *tmp_1 = i_y_768;
    float *tmp_2 = i_y_1024;
    float tmp_3[24 * 32];
    for (int i_3 = 0; i_3 < 24; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_128;
    float *tmp_5 = i_z_512;
    float tmp_6[4 * 16];
    for (int i_6 = 0; i_6 < 4; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 32; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 32 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[96 * 8];
    for (int i_7 = 0; i_7 < 96; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 768; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_128 float 128
// i_z_1024 float 1024
// i_z_384 float 384
// i_y_256 float 256
// result float 192
void slow_performance(float *i_y_128, float *i_z_1024, float *i_z_384, float *i_y_256, float *result)
{
    float *tmp_1 = i_y_128;
    float *tmp_2 = i_z_1024;
    float tmp_3[4 * 32];
    for (int i_3 = 0; i_3 < 4; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_384;
    float *tmp_5 = i_y_256;
    float tmp_6[24 * 16];
    for (int i_6 = 0; i_6 < 24; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 16; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 16 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[8 * 24];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 24; k_7++)
        {
            tmp_7[i_7 * 24 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 24 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 24 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_x_384 float 384
// i_x_192 float 192
// i_y_768 float 768
// result float 1024
void slow_performance(float *i_x_384, float *i_x_192, float *i_y_768, float *result)
{
    float *tmp_1 = i_x_384;
    float *tmp_2 = i_x_384;
    float tmp_3[8 * 8];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 8; k_3++)
        {
            tmp_3[i_3 * 8 + k_3] = 0;
            for (int j_3 = 0; j_3 < 48; j_3++)
            {
                tmp_3[i_3 * 8 + k_3] += tmp_1[i_3 * 48 + j_3] * tmp_2[j_3 * 8 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_192;
    float *tmp_5 = i_y_768;
    float tmp_6[8 * 32];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 32; k_6++)
        {
            tmp_6[i_6 * 32 + k_6] = 0;
            for (int j_6 = 0; j_6 < 24; j_6++)
            {
                tmp_6[i_6 * 32 + k_6] += tmp_4[i_6 * 24 + j_6] * tmp_5[j_6 * 32 + k_6];
            }
        }
    }
    float tmp_7[16 * 64];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 64; k_7++)
        {
            tmp_7[i_7 * 64 + k_7] = 0;
            for (int j_7 = 0; j_7 < 4; j_7++)
            {
                tmp_7[i_7 * 64 + k_7] += tmp_3[i_7 * 4 + j_7] * tmp_6[j_7 * 64 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_256 float 256
// i_y_192 float 192
// i_z_768 float 768
// result float 256
void slow_performance(float *i_y_256, float *i_y_192, float *i_z_768, float *result)
{
    float *tmp_1 = i_y_256;
    float tmp_2[64 * 4];
    for (int i_2 = 0; i_2 < 64; i_2++)
    {
        for (int j_2 = 0; j_2 < 4; j_2++)
        {
            tmp_2[j_2 * 64 + i_2] = tmp_1[i_2 * 4 + j_2];
        }
    }
    float *tmp_3 = i_y_192;
    float *tmp_4 = i_z_768;
    float tmp_5[8 * 32];
    for (int i_5 = 0; i_5 < 8; i_5++)
    {
        for (int k_5 = 0; k_5 < 32; k_5++)
        {
            tmp_5[i_5 * 32 + k_5] = 0;
            for (int j_5 = 0; j_5 < 24; j_5++)
            {
                tmp_5[i_5 * 32 + k_5] += tmp_3[i_5 * 24 + j_5] * tmp_4[j_5 * 32 + k_5];
            }
        }
    }
    float tmp_6[256 * 1];
    for (int i_6 = 0; i_6 < 256; i_6++)
    {
        for (int j_6 = 0; j_6 < 1; j_6++)
        {
            tmp_6[i_6 * 1 + j_6] = tmp_2[i_6 * 1 + j_6] + tmp_5[i_6 * 1 + j_6];
        }
    }
    for (int i_6 = 0; i_6 < 256; i_6++)
        result[i_6] = tmp_6[i_6];
}
/**********************************************************************************/
// i_x_256 float 256
// i_z_512 float 512
// i_y_768 float 768
// result float 512
void slow_performance(float *i_x_256, float *i_z_512, float *i_y_768, float *result)
{
    float *tmp_1 = i_x_256;
    float *tmp_2 = i_z_512;
    float tmp_3[8 * 16];
    for (int i_3 = 0; i_3 < 8; i_3++)
    {
        for (int k_3 = 0; k_3 < 16; k_3++)
        {
            tmp_3[i_3 * 16 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 16 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 16 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_768;
    float *tmp_5 = i_y_768;
    float tmp_6[16 * 16];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 48; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 48 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[16 * 32];
    for (int i_7 = 0; i_7 < 16; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_y_1024 float 1024
// result float 64
void slow_performance(float *i_y_1024, float *result)
{
    float *tmp_1 = i_y_1024;
    float *tmp_2 = i_y_1024;
    float *tmp_3 = i_y_1024;
    float tmp_4[16 * 16];
    for (int i_4 = 0; i_4 < 16; i_4++)
    {
        for (int k_4 = 0; k_4 < 16; k_4++)
        {
            tmp_4[i_4 * 16 + k_4] = 0;
            for (int j_4 = 0; j_4 < 64; j_4++)
            {
                tmp_4[i_4 * 16 + k_4] += tmp_2[i_4 * 64 + j_4] * tmp_3[j_4 * 16 + k_4];
            }
        }
    }
    float tmp_5[16 * 4];
    for (int i_5 = 0; i_5 < 16; i_5++)
    {
        for (int k_5 = 0; k_5 < 4; k_5++)
        {
            tmp_5[i_5 * 4 + k_5] = 0;
            for (int j_5 = 0; j_5 < 64; j_5++)
            {
                tmp_5[i_5 * 4 + k_5] += tmp_1[i_5 * 64 + j_5] * tmp_4[j_5 * 4 + k_5];
            }
        }
    }
    for (int i_5 = 0; i_5 < 64; i_5++)
        result[i_5] = tmp_5[i_5];
}
/**********************************************************************************/
// i_z_64 float 64
// i_x_1024 float 1024
// i_x_512 float 512
// result float 512
void slow_performance(float *i_z_64, float *i_x_1024, float *i_x_512, float *result)
{
    float *tmp_1 = i_z_64;
    float *tmp_2 = i_x_1024;
    float tmp_3[4 * 64];
    for (int i_3 = 0; i_3 < 4; i_3++)
    {
        for (int k_3 = 0; k_3 < 64; k_3++)
        {
            tmp_3[i_3 * 64 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 64 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 64 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_512;
    float *tmp_5 = i_x_1024;
    float tmp_6[8 * 16];
    for (int i_6 = 0; i_6 < 8; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 64; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 64 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[32 * 16];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 8; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 512; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_192 float 192
// i_y_384 float 384
// i_y_512 float 512
// i_x_64 float 64
// result float 1024
void slow_performance(float *i_z_192, float *i_y_384, float *i_y_512, float *i_x_64, float *result)
{
    float *tmp_1 = i_z_192;
    float *tmp_2 = i_y_384;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 12; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 12 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_y_512;
    float *tmp_5 = i_x_64;
    float tmp_6[64 * 8];
    for (int i_6 = 0; i_6 < 64; i_6++)
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
    float tmp_7[32 * 32];
    for (int i_7 = 0; i_7 < 32; i_7++)
    {
        for (int k_7 = 0; k_7 < 32; k_7++)
        {
            tmp_7[i_7 * 32 + k_7] = 0;
            for (int j_7 = 0; j_7 < 16; j_7++)
            {
                tmp_7[i_7 * 32 + k_7] += tmp_3[i_7 * 16 + j_7] * tmp_6[j_7 * 32 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 1024; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_192 float 192
// i_y_1024 float 1024
// i_x_128 float 128
// i_x_512 float 512
// result float 192
void slow_performance(float *i_z_192, float *i_y_1024, float *i_x_128, float *i_x_512, float *result)
{
    float *tmp_1 = i_z_192;
    float *tmp_2 = i_y_1024;
    float tmp_3[12 * 64];
    for (int i_3 = 0; i_3 < 12; i_3++)
    {
        for (int k_3 = 0; k_3 < 64; k_3++)
        {
            tmp_3[i_3 * 64 + k_3] = 0;
            for (int j_3 = 0; j_3 < 16; j_3++)
            {
                tmp_3[i_3 * 64 + k_3] += tmp_1[i_3 * 16 + j_3] * tmp_2[j_3 * 64 + k_3];
            }
        }
    }
    float *tmp_4 = i_x_128;
    float *tmp_5 = i_x_512;
    float tmp_6[16 * 64];
    for (int i_6 = 0; i_6 < 16; i_6++)
    {
        for (int k_6 = 0; k_6 < 64; k_6++)
        {
            tmp_6[i_6 * 64 + k_6] = 0;
            for (int j_6 = 0; j_6 < 8; j_6++)
            {
                tmp_6[i_6 * 64 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 64 + k_6];
            }
        }
    }
    float tmp_7[12 * 16];
    for (int i_7 = 0; i_7 < 12; i_7++)
    {
        for (int k_7 = 0; k_7 < 16; k_7++)
        {
            tmp_7[i_7 * 16 + k_7] = 0;
            for (int j_7 = 0; j_7 < 64; j_7++)
            {
                tmp_7[i_7 * 16 + k_7] += tmp_3[i_7 * 64 + j_7] * tmp_6[j_7 * 16 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 192; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
// i_z_512 float 512
// i_z_1024 float 1024
// i_z_128 float 128
// i_z_64 float 64
// result float 64
void slow_performance(float *i_z_512, float *i_z_1024, float *i_z_128, float *i_z_64, float *result)
{
    float *tmp_1 = i_z_512;
    float *tmp_2 = i_z_1024;
    float tmp_3[16 * 32];
    for (int i_3 = 0; i_3 < 16; i_3++)
    {
        for (int k_3 = 0; k_3 < 32; k_3++)
        {
            tmp_3[i_3 * 32 + k_3] = 0;
            for (int j_3 = 0; j_3 < 32; j_3++)
            {
                tmp_3[i_3 * 32 + k_3] += tmp_1[i_3 * 32 + j_3] * tmp_2[j_3 * 32 + k_3];
            }
        }
    }
    float *tmp_4 = i_z_128;
    float *tmp_5 = i_z_64;
    float tmp_6[32 * 16];
    for (int i_6 = 0; i_6 < 32; i_6++)
    {
        for (int k_6 = 0; k_6 < 16; k_6++)
        {
            tmp_6[i_6 * 16 + k_6] = 0;
            for (int j_6 = 0; j_6 < 4; j_6++)
            {
                tmp_6[i_6 * 16 + k_6] += tmp_4[i_6 * 4 + j_6] * tmp_5[j_6 * 16 + k_6];
            }
        }
    }
    float tmp_7[8 * 8];
    for (int i_7 = 0; i_7 < 8; i_7++)
    {
        for (int k_7 = 0; k_7 < 8; k_7++)
        {
            tmp_7[i_7 * 8 + k_7] = 0;
            for (int j_7 = 0; j_7 < 64; j_7++)
            {
                tmp_7[i_7 * 8 + k_7] += tmp_3[i_7 * 64 + j_7] * tmp_6[j_7 * 8 + k_7];
            }
        }
    }
    for (int i_7 = 0; i_7 < 64; i_7++)
        result[i_7] = tmp_7[i_7];
}
/**********************************************************************************/
