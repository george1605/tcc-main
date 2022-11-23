#ifndef __NEW__
#define __NEW__
#include <malloc.h>
#include "throw.h"
#define new(type) __runt_alloc(sizeof(type))
#define news(type, sz) __runt_alloc(sizeof(type) * sz)
#define delete(ptr) __runt_free(ptr)

static char* badalloc_exc()
{
    return "Failed to allocate!";
}

struct bad_alloc
{
    char*(*what)();
};

void new_badalloc()
{
    struct bad_alloc bd;
    bd.what = badalloc_exc;
}

void* __runt_alloc(size_t sz)
{
    void* c;
    if(!(c = malloc(sz)))
    {
        seterr {"Failed to allocate!", 1};
        throw;
    }
    return c;
}

void __runt_free(void* ptr)
{
    if(ptr)
        free(ptr);
}
#endif