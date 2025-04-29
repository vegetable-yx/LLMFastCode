#pragma once

#include <string>

typedef void(*comp_func)(double* x, double* y, double* z);
void add_function(comp_func f, std::string name);