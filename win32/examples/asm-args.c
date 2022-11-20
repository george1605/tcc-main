#include <stdio.h>

int main(int argc, char** argv)
{
    int p, r;
    asm("add %eax, %ebx");
    asm("mov %%ebx, %0":"=r"(p):"r"(r));
    printf("%i", p);
}