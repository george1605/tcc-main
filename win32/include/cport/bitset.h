#ifndef __BITSET__
#define __BITSET__
#include <stdint.h>
#include <string.h>
#include <malloc.h>

#define BIT_SET(number, x) number |= (1 << x)
#define BIT_GET(number, x) number & (1 << x)
#define BIT_UNSET(number, x) number &= ~(1 << x)

struct bitset
{
    int* number;
    size_t size;
};

struct bitset bitset_alloc(size_t size)
{
    struct bitset bt;
    bt.size = size;
    bt.number = (int*)malloc(size);
}

char bitset_getc(struct bitset* p, size_t pos)
{
    if(!p)
        return 0;
    return *(char*)(p->number + pos);
}

// IEEE 754 - Floating Point 
struct floating
{
    uint8_t sign: 1;
    uint8_t exp: 8;
    uint32_t mantissa: 23;
};

struct floating48
{
    uint8_t sign: 1;
    uint32_t mant1: 23;
    uint8_t ignore: 1;
    uint16_t mant2: 14;
    uint8_t e_sign: 1;
    uint8_t exp: 8;
};

void get_floating(float number, struct floating* p)
{
    memcpy(p, &number, sizeof(int));
}

void sign_int(int* number, char sign)
{
    *number |= (sign * (1 << 31));
}

#endif