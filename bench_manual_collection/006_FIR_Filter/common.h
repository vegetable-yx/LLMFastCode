#pragma once

#include <string>

typedef void (*comp_func)(double *x, double *y, double *h, int n, int m);
void add_function(comp_func f, std::string name);
void kernel_base(double *x, double *y, double *h, int n, int m);