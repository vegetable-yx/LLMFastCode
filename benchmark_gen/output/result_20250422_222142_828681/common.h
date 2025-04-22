#pragma once

#include <string>

typedef void (*bench_func)(float *i_z_128, float *i_y_32, float *i_y_16, float *i_z_64, float *result);

void add_function(bench_func f, std::string name);