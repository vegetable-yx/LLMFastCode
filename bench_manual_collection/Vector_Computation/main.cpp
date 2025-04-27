/**
 *      _________   _____________________  ____  ______
 *     / ____/   | / ___/_  __/ ____/ __ \/ __ \/ ____/
 *    / /_  / /| | \__ \ / / / /   / / / / / / / __/
 *   / __/ / ___ |___/ // / / /___/ /_/ / /_/ / /___
 *  /_/   /_/  |_/____//_/  \____/\____/_____/_____/
 *
 *  http://www.acl.inf.ethz.ch/teaching/fastcode
 *  How to Write Fast Numerical Code 263-2300 - ETH Zurich
 *  Copyright (C) 2019
 *                   Tyler Smith        (smitht@inf.ethz.ch)
 *                   Alen Stojanov      (astojanov@inf.ethz.ch)
 *                   Gagandeep Singh    (gsingh@inf.ethz.ch)
 *                   Markus Pueschel    (pueschel@inf.ethz.ch)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see http://www.gnu.org/licenses/.
 */
// #include "stdafx.h"

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <random>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "tsc_x86.h"

using namespace std;

#define N 1024
#define CYCLES_REQUIRED (1 * 1e8)
#define REP 50
#define EPS (1e-3)

void kernel_base(double *x, double *y, double *z)
{
  for (int i = 0; i < N; i++)
  {
    double a = i % 2 ? x[i - 1] : x[i + 1];
    double b = y[i];
    if (round(a) > round(b))
    {
      z[i] = a + a * b;
    }
    else
    {
      z[i] = b - 3 * i;
    }
  }
}

/* prototype of the function you need to optimize */
typedef void (*comp_func)(double *, double *, double *);

// headers
void register_functions();
double get_perf_score(comp_func f);
double perf_test(comp_func f, string desc, int flops);
void add_function(comp_func f, string name);

/* Global vars, used to keep track of student functions */
vector<comp_func> userFuncs;
vector<string> funcNames;
vector<int> funcFlops;
int numFuncs = 0;

template <typename T>
void rands(T *m, size_t row, size_t col)
{
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<T> dist(-1.0, 1.0);
  for (size_t i = 0; i < row * col; ++i)
    m[i] = dist(gen);
}

template <typename T>
void build(T **a, int m, int n)
{
  *a = static_cast<T *>(aligned_alloc(32, m * n * sizeof(T)));
  rands(*a, m, n);
}

template <typename T>
void destroy(T *m)
{
  free(m);
}

template <typename T>
T nrm_sqr_diff(T *x, T *y, int n)
{
  T nrm_sqr = 0.0;
  for (int i = 0; i < n; i++)
  {
    nrm_sqr += (x[i] - y[i]) * (x[i] - y[i]);
  }

  if (isnan(nrm_sqr))
  {
    nrm_sqr = INFINITY;
  }

  return nrm_sqr;
}

/*
 * Registers a user function to be tested by the driver program. Registers a
 * string description of the function as well
 */
void add_function(comp_func f, string name)
{
  userFuncs.push_back(f);
  funcNames.emplace_back(name);
  numFuncs++;
}

/*
 * Checks the given function for validity. If valid, then computes and
 * reports and returns the number of cycles required per iteration
 */
double perf_test(comp_func f, string desc, int flops)
{
  double cycles = 0.;
  long num_runs = 100;
  double multiplier = 1;
  myInt64 start, end;

  static double x[N] __attribute__((aligned(32)));
  static double y[N] __attribute__((aligned(32)));
  static double z[N] __attribute__((aligned(32)));
  rands(x, N, 1);
  rands(y, N, 1);
  rands(z, N, 1);

  // Warm-up phase: we determine a number of executions that allows
  // the code to be executed for at least CYCLES_REQUIRED cycles.
  // This helps excluding timing overhead when measuring small runtimes.
  do
  {
    num_runs = num_runs * multiplier;
    start = start_tsc();
    for (size_t i = 0; i < num_runs; i++)
    {
      f(x, y, z);
    }
    end = stop_tsc(start);

    cycles = (double)end;
    multiplier = (CYCLES_REQUIRED) / (cycles);

  } while (multiplier > 2);

  list<double> cyclesList;

  // Actual performance measurements repeated REP times.
  // We simply store all results and compute medians during post-processing.
  double total_cycles = 0;
  for (size_t j = 0; j < REP; j++)
  {

    start = start_tsc();
    for (size_t i = 0; i < num_runs; ++i)
    {
      f(x, y, z);
    }
    end = stop_tsc(start);

    cycles = ((double)end) / num_runs;
    total_cycles += cycles;

    cyclesList.push_back(cycles);
  }
  total_cycles /= REP;

  cycles = total_cycles;
  cyclesList.sort();
  return cycles; // cyclesList.front();
}

int main(int argc, char **argv)
{
  cout << "Starting program. ";
  double perf;
  int i;

  register_functions();

  if (numFuncs == 0)
  {
    cout << endl;
    cout << "No functions registered - nothing for driver to do" << endl;
    cout << "Register functions by calling register_func(f, name)" << endl;
    cout << "in register_funcs()" << endl;

    return 0;
  }
  cout << numFuncs << " functions registered." << endl;

  // Check validity of functions.
  static double x[N] __attribute__((aligned(32)));
  static double y[N] __attribute__((aligned(32)));
  static double z[N] __attribute__((aligned(32)));
  rands(x, N, 1);
  rands(y, N, 1);
  rands(z, N, 1);

  double *z_base = static_cast<double *>(malloc(N * sizeof(double)));
  double *z_old = static_cast<double *>(malloc(N * sizeof(double)));

  for (int _ = 0; _ < 1; _++)
  {
    memcpy(z_old, z, N * sizeof(double));
    memcpy(z_base, z, N * sizeof(double));
    kernel_base(x, y, z_base);
    for (i = 0; i < numFuncs; i++)
    {
      memcpy(z, z_old, N * sizeof(double));
      comp_func f = userFuncs[i];
      f(x, y, z);
      double error = nrm_sqr_diff(z, z_base, N);

      if (error > EPS)
      {
        cout << "\033[1;31m" << "The result of the " << i + 1 << "th function is not correct." << "\033[0m" << std::endl;
      }
    }
  }

  destroy(z_base);
  destroy(z_old);

  for (i = 0; i < numFuncs; i++)
  {
    perf = perf_test(userFuncs[i], funcNames[i], 1);
    cout << endl
         << "Running: " << funcNames[i] << endl;
    cout << perf << " cycles" << endl;
  }

  return 0;
}