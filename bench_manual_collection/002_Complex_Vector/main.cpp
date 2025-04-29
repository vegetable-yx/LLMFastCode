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

 #include <list>
 #include <vector>
 #include <string>
 #include <iostream>
 #include <algorithm>
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <math.h>
 #include <string.h>
 #include "tsc_x86.h"
 #include "utils.h"
 
 using namespace std;
 
 #define N 1024
 
 #define NR 32
 #define CYCLES_REQUIRED 1e8
 #define REP 50
 #define EPS (1e-3)
 
 void kernel_base(double *x, double *y, double *z)
 {
   double t[2];
   for (int i = 0; i < N; i++)
   {
     if (sqrt(x[i * 2] * x[i * 2] + x[i * 2 + 1] * x[i * 2 + 1]) > sqrt(y[i * 2] * y[i * 2] + y[i * 2 + 1] * y[i * 2 + 1]))
     {
       unsigned int k = floor(4.0 * z[i]);
       switch (k)
       {
       case 0:
         t[0] = x[i * 2] + y[i * 2] * 5.1;
         t[1] = x[i * 2 + 1] + y[i * 2 + 1] * 5.1;
         break;
       case 1:
         t[0] = (x[i * 2]) * (y[i * 2] * 2.1) - (x[i * 2 + 1]) * (y[i * 2 + 1] * 2.1);
         t[1] = (x[i * 2]) * (y[i * 2 + 1] * 2.1) + (x[i * 2 + 1]) * (y[i * 2] * 2.1);
         break;
       case 2:
         t[0] = x[i * 2] + y[i * 2] * (-3.5);
         t[1] = x[i * 2 + 1] + y[i * 2 + 1] * (-3.5);
         break;
       case 3:
         t[0] = (x[i * 2]) * (y[i * 2] * (-4.1)) - (x[i * 2 + 1]) * (y[i * 2 + 1] * (-4.1));
         t[1] = (x[i * 2]) * (y[i * 2 + 1] * (-4.1)) + (x[i * 2 + 1]) * (y[i * 2] * (-4.1));
         break;
       default:
         break;
       }
       z[i] += t[0] + ((t[0]) * (t[0]) - (t[1]) * (t[1]));
     }
     else
     {
       z[i] += round(((x[i * 2]) * (x[i * 2]) - (x[i * 2 + 1]) * (x[i * 2 + 1]))) + pow(sqrt(y[i * 2] * y[i * 2] + y[i * 2 + 1] * y[i * 2 + 1]), 2.0);
     }
   }
 }
 
 /* prototype of the function you need to optimize */
 typedef void (*comp_func)(double *x, double *y, double *z);
 
 void register_functions();
 double get_perf_score(comp_func f);
 double perf_test(comp_func f, string desc, int flops);
 void add_function(comp_func f, string name);
 
 /* Global vars, used to keep track of student functions */
 vector<comp_func> userFuncs;
 vector<string> funcNames;
 vector<int> funcFlops;
 int numFuncs = 0;
 
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
 
   static double x[2 * N] __attribute__((aligned(32)));
   static double y[2 * N] __attribute__((aligned(32)));
   static double z[1 * N] __attribute__((aligned(32)));
   static double z_bk[1 * N] __attribute__((aligned(32)));
 
   rands(x, 2 * N, 1);
   rands(y, 2 * N, 1);
   rands(z, 1 * N, 1);
   rands(z_bk, 1 * N, 1);
   rands(z, N, 1, 0.0, 0.999);
   copy_n(z, N, z_bk);
 
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
       copy_n(z_bk, N, z);
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
     // Do all reps with different inputs
     rands(z, N, 1, 0.0, 0.999);
     copy_n(z, N, z_bk);
 
     start = start_tsc();
     for (size_t i = 0; i < num_runs; ++i)
     {
       f(x, y, z);
       copy_n(z_bk, N, z);
     }
     end = stop_tsc(start);
 
     cycles = ((double)end) / num_runs;
     total_cycles += cycles;
 
     cyclesList.push_back(cycles);
   }
   total_cycles /= REP;
   cycles = total_cycles;
 
   return cycles;
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
   static double x[2 * N] __attribute__((aligned(32)));
   static double y[2 * N] __attribute__((aligned(32)));
   static double z[1 * N] __attribute__((aligned(32)));
   static double z_base[1 * N] __attribute__((aligned(32)));
   static double z_copy[1 * N] __attribute__((aligned(32)));
 
   rands(x, 2 * N, 1);
   rands(y, 2 * N, 1);
   rands(z, 1 * N, 1);
   rands(z_base, 1 * N, 1);
   rands(z_copy, 1 * N, 1);
   rands(z, N, 1, 0.0, 0.999);
   copy_n(z, N, z_base);
   copy_n(z, N, z_copy);
 
   kernel_base(x, y, z_base);
 
   for (i = 0; i < numFuncs; i++)
   {
     comp_func f = userFuncs[i];
     f(x, y, z);
 
     double error = nrm_sqr_diff((double *)z, (double *)z_base, N);
     if (error > EPS)
     {
       cout << "\033[1;31m" << "The result of the " << i + 1 << "th function is not correct." << "\033[0m" << std::endl;
     }
     copy_n(z_copy, N, z);
   }
 
   for (i = 0; i < numFuncs; i++)
   {
     perf = perf_test(userFuncs[i], funcNames[i], 1);
     cout << endl
          << "Running: " << funcNames[i] << endl;
     cout << perf << " cycles" << endl;
   }
 
   return 0;
 }