#include <stdio.h>
#include <holyc.h>
U8 buffer[32] = {0};

I32 main()
{
    GetS(buffer);
    puts(buffer);
}