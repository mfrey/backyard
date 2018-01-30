#include "foo.h"

#include <stdio.h>

void argh(void)
{
    printf("a from foo.{h,c}: %p \n", &a);
}
