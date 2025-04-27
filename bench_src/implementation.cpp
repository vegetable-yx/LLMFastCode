#include <immintrin.h>
#include <cstring>
#include "common.h"

/* LLM prompt code start */

// [Slow performance function]

/* Max performance function start */
// [Max performance function]
/* Max performance function end */

/* LLM prompt code end */

/*
 * Called by the driver to register your functions
 * Use add_function(func, description) to add your own functions
 */
void register_functions()
{
    add_function(&slow_performance, "slow_performance");
    add_function(&max_performance, "max_performance");
}