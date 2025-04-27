#include <string>
typedef void (*comp_func)(double *, double *);
void add_function(comp_func f, std::string name);
void kernel_base(double *x , double *y);