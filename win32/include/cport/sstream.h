#ifndef __SSTREAM__
#define __SSTREAM__
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "ios.h"
#ifdef __cplusplus
extern "C" {
#endif


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