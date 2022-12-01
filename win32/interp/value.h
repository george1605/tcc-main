#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define TYPE_NUMBER 1
#define TYPE_STRING 2
#define TYPE_BOOL 4
#define TYPE_ANY 8

struct Value
{
    void* ptr;
    size_t type, size;
};

struct Debug
{
    size_t alloc;
    FILE* log;
} _dbg;

struct Value new_val(size_t sz)
{
    #ifdef _MONITOR_
        _dbg.alloc += sz;
        fprintf(_dbg.log, "Allocated %i", sz);
    #endif
    struct Value i;
    i.ptr = malloc(sz);
    i.size = sz, i.type = TYPE_ANY;
    return i;
}

void free_val(struct Value val)
{
    free(val.ptr);
    val.size = 0, val.type = 0;
}

struct Stack
{
    struct Value* values;
    size_t size, cnt;
};

void push_stack(struct Stack stk, struct Value val)
{
    stk.values[stk.cnt++] = val;
}

struct Value pop_stack(struct Stack stk)
{
    if(stk.cnt < 0)
        return (struct Value){0, 0};
    return stk.values[stk.cnt--]; 
}

struct Stack alloc_stack(size_t sz)
{
    struct Stack i;
    i.cnt = 0;
    i.size = sz;
    i.values = malloc(sizeof(struct Value) * sz);
    return i;
}

void grow_stack(struct Stack* stk, size_t i)
{
    stk->size = i;
    stk->values = realloc(stk->values, i);
}

struct ProcState
{
    struct Stack stack;
    int(*main)(int argc, char** argv);   
};

struct ProcState init_proc()
{
    struct ProcState prc;
    prc.stack = alloc_stack(10);
    prc.main = NULL;
    return prc;
}

void free_proc(struct ProcState prc)
{
    prc.main = NULL;
    while(prc.stack.cnt != 0)
        pop_stack(prc.stack);
}

struct Function
{
    char* name;
    void* ptr;
} *funcs;
static size_t func_no = 0, func_cnt = 10;

void export_func(void(*f)(), char* name)
{
    if(func_no++ > func_cnt)
        funcs = realloc(funcs, sizeof(struct Function) * func_no);
    struct Function fnc;
    fnc.name = strdup(name);
    fnc.ptr = f;
    funcs[func_no] = fnc;
}

void* load_func(char* name)
{
    for(int i = 0;i < func_no;i++)
        if(!strcmp(funcs[i].name, name))
            return funcs[i].ptr;
}