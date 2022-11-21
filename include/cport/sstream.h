#ifndef __SSTREAM__
#define __SSTREAM__
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

enum ios
{
    app = 1,
    ate = 2,
    binary = 4,
    in = 8,
    out = 16,
    truncate = 32
};

struct stringstream
{
    FILE* file;
    void* buffer;
    int flags, pos;
};

#ifdef __cplusplus
}
#endif

#endif