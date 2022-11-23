#ifndef __FSTREAM__
#define __FSTREAM__
#include <stdio.h>
#include <malloc.h>

struct istream
{
    char* buffer;
    FILE* file;
};

#endif