#pragma once

#include <string>

typedef void (*comp_func)(double *x, double *y, int n);
void add_function(comp_func f, std::string name);
void kernel_base(double *x, double *y, int n);