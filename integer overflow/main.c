
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "common.h"

int main(int argc, char** argv){
    //uint32_t a = 42;
    //uint32_t b = 23;
    int a = INT_MAX;
    int b = INT_MAX;

    if (INT_MULT_OVERFLOW_P(a, b)) {
        printf("safe to multiply %d * %d = %d\n", a, b, a * b);
    } else {
        printf("nope\n");
    }

    return 0;
}
