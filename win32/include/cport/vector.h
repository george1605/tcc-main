#ifndef __VECTOR__
#define __VECTOR__
#include "new.h"
#define VECTOR(of) struct vector_ ## of

VECTOR(base)
{
    void* ptr;
    size_t size, count;
};

VECTOR(base) vec_alloc(size_t sz)
{
    struct vector_base bs;
    bs.count = 0;
    bs.size = sz;
    bs.ptr = news(char, sz);
    return bs;
}

#endif