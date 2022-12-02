#include <cport/bitset.h>
#include <stdio.h>

int main()
{
    int x = 100;
    sign_int(&x, 1);
    printf("%i", x);
}