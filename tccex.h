#pragma once
#include "libtcc.h"
#include <stdio.h>

LIBTCCAPI TCCState *tcc_loaddrv(const char *path)
{
    TCCState *s = tcc_new();
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
    if (tcc_add(s, path) == -1)
    {
        printf("No file named %s", path);
        return s;
    }
    tcc_compile(s);
    if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0)
    {
        puts("Cannot relocate the program.");
    }
    return s;
}
