/**
 * @brief A simple example for GCCs builtin functions for
 * detecting integer overflows
 *
 * Compile via:
 *    gcc -Wall main.c
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "common.h"

int main(int argc, char** argv){
    int a = INT_MAX;
    int b = INT_MAX;
    int c;

    if (!INT_ADD_OVERFLOW(a, b, &c)) {
        printf("safe to multiply %d * %d = %d\n", a, b, c);
    } else {
        printf("it is not safe to multiply %d * %d\n", a, b);
    }

    return 0;
}
