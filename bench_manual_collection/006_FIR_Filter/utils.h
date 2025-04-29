#pragma once
#include <random>

template<typename T>
void rands(T * m, size_t len)
{
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<T> dist(-1.0, 1.0);
    for (size_t i = 0; i < len; ++i)  
        m[i] = dist(gen);
}

template<typename T>
void destroy(T* m)
{
    free(m);
}

template<typename T>
T nrm_sqr_diff(T *x, T *y, int n) {
    T nrm_sqr = 0.0;
    for(int i = 0; i < n; i++) {
        nrm_sqr += (x[i] - y[i]) * (x[i] - y[i]);
    }
    
    if (isnan(nrm_sqr)) {
      nrm_sqr = INFINITY;
    }
    
    return nrm_sqr;
}