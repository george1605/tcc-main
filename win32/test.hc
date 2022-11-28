#include <stdio.h>
#include <holyc.h>

U0 test()
{
    puts("nope");
}

I32 main()
{
    Asm(call test);
}