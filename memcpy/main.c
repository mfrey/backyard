/**
 * don't try this at home
 * http://www.mathyvanhoef.com/2013/02/understanding-heap-exploiting-heap.html
 */
#include <stdlib.h>
#include <string.h>

int
ccnl_ndntlv_prependBlob(int type, unsigned char *blob, int len,
                         int *offset, unsigned char *buf)
{
     int oldoffset = *offset;

     if (*offset < len)
         return -1;
     memcpy(buf + *offset - len, blob, len);
     *offset -= len;
//     if (ccnl_ndntlv_prependTL(type, len, offset, buf) < 0)
//        return -1;
     return oldoffset - *offset;
}


int main(int argc, char** argv)
{
    int length = 5;
    int offset = 3;
    int buffersize = 23;
    unsigned char *buffer = malloc(buffersize * sizeof(unsigned char));


    ccnl_ndntlv_prependBlob(10, buffer, length, &offset, buffer);

    return 0;
}
