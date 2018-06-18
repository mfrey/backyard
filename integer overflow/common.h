
#ifndef COMMON_H_
#define COMMON_H_

#define INT_MULT_OVERFLOW_P(a, b) \
    __builtin_mul_overflow_p (a, b, (__typeof__ ((a) * (b))) 0)

#endif 

