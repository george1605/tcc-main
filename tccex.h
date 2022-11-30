#ifndef __TCCEX__
#define __TCCEX__
#include "libtcc.h"
#include <stdio.h>
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

// Read include file
void tcc_compilefile(TCCState* s, const char* lib)
{
    if(s == NULL)
        s = tcc_new();
    FILE* fp = fopen(lib, "r");
    long sz = ftell(fp);
    char* mem = malloc(sz + 1);
    fread(mem, 1, sz, fp);
    tcc_compile_string(s, mem);
    free(mem);
}

int tcc_isextern(TCCState* s, const char* name)
{
    if(!tcc_get_symbol(s, name))
        return TCC_NOTDEF;
    return TCC_MAINSYM; // TO DO!
}

void tcc_runsrc(TCCState* s, const char* src)
{
    if(!tcc_compile_string(s, src))
        return;
    tcc_run(s, 0, NULL);
}

void tcc_add_defs(TCCState* s)
{
    tcc_define_symbol(s, "__FILE__", s->files[0]->name);
    tcc_define_symbol(s, "__CVERSION__", "201402L");
}

#ifdef _WIN32
int tcc_linkwin32(TCCState* s)
{
    tcc_add_library(s, "user32");
    tcc_add_library(s, "kernel32");
    tcc_add_include_path(s, "minwindef.h"); 
}
#endif

#endif