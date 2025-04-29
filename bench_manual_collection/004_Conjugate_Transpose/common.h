#pragma once

#include <string>
#include "complex.h"

typedef void (*comp_func)(double *x, double *y);
void add_function(comp_func f, std::string name);
void kernel_base(double *A, double *x, double *y, int);