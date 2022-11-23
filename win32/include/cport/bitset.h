#ifndef __BITSET__
#define __BITSET__
#include <stdint.h>
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

#endif