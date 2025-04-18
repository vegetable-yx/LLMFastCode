#pragma once

#include <string>

typedef struct
{
    double re;
    double im;
} complex_t;

typedef void (*comp_func)(complex_t x[4][4], complex_t y[4][4]);
void add_function(comp_func f, std::string name);
void kernel_base(double *A, double *x, double *y, int);