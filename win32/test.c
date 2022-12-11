#include <ints.h>
#include <stdio.h>

int main()
{
    u16_t q = {.hi = 0x77, .low = 0xa0};
    uint_t p = get_short(&q);
    printf("%i", p);
}