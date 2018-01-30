#include "foo.h"
#include "bar.h"

#include <stdio.h>

void example(void)
{
    printf("a from bar.{h,c}: %p \n", &a);
    argh();
}
