#include <stdio.h>
#include <holyc.h>
U8 buffer[32] = {0};

I32 main()
{
    FILE* p = fopen("try.x", "w");
    fputc('A', p);
    return 0;
}