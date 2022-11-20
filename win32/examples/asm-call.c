#include <stdio.h>

void test()
{
        puts("Hello World!");
}

int main()
{
    asm ("call test");
    return 0;
}