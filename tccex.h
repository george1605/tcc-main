#ifndef __TCCEX__
#define __TCCEX__
#include "libtcc.h"
#include <string.h>

typedef struct
{
    const char* var;
    void* ptr;
    TCCState* state; // pointer to the program
} TCCWatch;

LIBTCCAPI TCCState *tcc_loaddrv(const char *path)
{
    TCCState *s = tcc_new();
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
    if (tcc_add_library(s, path) == -1)
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

TCCWatch* tcc_watch(TCCState* s, char* name)
{
    TCCWatch* wtc = (TCCWatch*)malloc(sizeof(TCCWatch));
    wtc->var = name;
    wtc->state = s;
    wtc->ptr = tcc_get_symbol(s, name);
    return wtc;
}

void tcc_wstep(void(*f)(), TCCWatch* wtc)
{
    f();
    wtc->ptr = tcc_get_symbol(wtc->state, wtc->var);
}

int tcc_wadd(TCCWatch* wtc, void* val)
{
    return tcc_add_symbol(wtc->state, wtc->var, val);
}

#define TCC_NOTDEF 0x100
#define TCC_EXTERNSYM 0x200
#define TCC_MAINSYM 0x10

int tcc_haslib(TCCState* s, const char* lib)
{
    int i;
    for(i = 1;i < s->nb_include_paths;i++)
        if(!strcmp(s->include_paths[i], lib))
            return 1;
    return 0;
}

int tcc_isextern(TCCState* s, const char* name)
{
    if(!tcc_get_symbol(s, name))
        return TCC_NOTDEF;
    return TCC_MAINSYM; // TO DO!
}

#endif