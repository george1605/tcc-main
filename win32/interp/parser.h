#include <string.h>
#include <stdint.h>
#ifdef __unix__
#include <dlfcn.h>
#else
#include <windows.h>
#endif

#include "value.h"
#define TOKEN(value, type) (struct token){ value, type }
#define ERR_DOLARVAR 0x10
#define ERR_NOEQUAL 0x20

#define TOKEN_DEF 0x10
#define TOKEN_EOF 0xFF
#define TOKEN_REG 0x20
#define TOKEN_OP  0x40

struct Stack def_stk;
static int(*__cdecl error_func)(const char*) = puts;
char* keywords[] = {
    "def",
    "push",
    "pop",
    "alloc",
    "free",
    "print",
    "getkey",
    "call"
};

void parse_print(const char* str)
{
    char* p = strtok(str, " ");
    p = strtok(NULL, " ");
    if(!p)
    {
        struct Value v = pop_stack(def_stk);
        if(v.size == 1)
        {
            putc((char)v.ptr, stdout);
            return 0;
        }
        p = pop_stack(def_stk).ptr; // pops from the stack
    }
    puts(p);
}

void add_keyword(const char* kwd, void(*parser)(const char*))
{
    realloc(keywords, sizeof keywords + sizeof kwd);
}

void* get_dl(const char* lib, const char* name)
{
#ifdef __unix__
    void* handle = dlopen(lib, RTDL_NOW);
    return dlsym(handle, name);
#elif defined(_WIN32)
    HMODULE mod = LoadLibraryA(lib);
    return (void*)GetProcAddress(mod, name);
#endif
}
// calls to dynamic linked libs
void* parse_load(const char* p)
{
    // if(strncmp(p, "load", 4) != 0)
    //    return NULL;
    char* r = strtok(p, " ");
    char* rp = strtok(NULL, "@");
    return get_dl(r, rp);
}

struct token
{
    char* value;
    int type;
};

struct token* alloc_tokens(size_t size)
{
    struct token* p = (struct token*)malloc(sizeof(struct token) * size);
    p[size - 1].type = TOKEN_EOF;
}

void get_tokens(const char* str, struct token* tokens)
{
    char* p = strtok((char*)str, " ");
    int c = 0;
    while(p != NULL && tokens[c].type != TOKEN_EOF)
    {
        tokens[c++] = (struct token){p, TOKEN_DEF};
        p = strtok(NULL, " ");
    }
}

void load_file(const char* filename, struct token* tokens)
{
    char buf[100];
    FILE* f = fopen(filename, "r");
    fread(buf, 1, sizeof buf, f);
    get_tokens(buf, tokens);
}

double mathexec(struct token* tokens)
{
    int inum = atoi(tokens[0].value);
    int fnum = atoi(tokens[2].value);
    char op = *tokens[1].value;
    switch(op)
    {
        case '+':
            return inum + fnum;
        case '-':
            return inum - fnum;
        case '*':
            return inum * fnum;
        default:
            return 0;
    }
}

typedef FILE* FStream;
char parse_getkey(const char* _fname)
{
    if(!_fname)
        return fgetc(stdin);
    FStream f = fopen(_fname, "r");
    char c = fgetc(f);
    fclose(f);
    struct Value p;
    p.ptr = (void*)c;
    p.size = 1;
    push_stack(def_stk, p);
    return c;
}

void parse_math(const char* p)
{
    struct token* tokens = alloc_tokens(10);
    get_tokens(p, tokens);
    double value = mathexec(tokens);
    double* ptr = calloc(1, sizeof(double));
    *ptr = value;
    struct Value val = (struct Value) {.type = TYPE_NUMBER, .ptr = ptr};
    push_stack(def_stk, val);
}

void init_intrp()
{
    def_stk = alloc_stack(50);
    funcs = malloc(sizeof(struct Function) * func_cnt);
}

static int strfind(char* f, char p)
{
    int k = 0;
    while(f[k] && f[k] != p)
        k++;
    if(!f[k])
        return -1;
    return k;
}

struct Value parse_type(const char* str)
{
    if(str[0] > '0' && str[0] <= '9')
        return (struct Value){ (void*)atoi(str), TYPE_NUMBER, 4 };
    if(str[0] == '"')
        return (struct Value){ (void*)(str + 1), TYPE_STRING, strfind((char*)str + 1, '"')};
    if(str[0] == '\x27')
        return (struct Value){ (void*)str[1], TYPE_CHAR, 1 };
    if(!strcmp(str, "true") || !strcmp(str, "false"))
        return (struct Value){ (void*)(str[0] == 't'), TYPE_BOOL, 1 };
    return new_val(0);
}

// push or pop commands
void parse_stack(const char* p, struct Stack stk)
{
    if(!strncmp(p, "push", 4))
    {
        char* c = strtok(p, " ");
        push_stack(stk, parse_type(c));
    } else {
        pop_stack(stk);
    }
}

struct Stack parse_array(const char* p)
{
    if(p[0] != '[' || p[1] == ']')
    {
        error_func("Expected '[' or ']'");
        return (struct Stack){NULL};
    }
    struct Stack s = alloc_stack(10);
    int k = 0, sz = 10;
    while(p[k] != ']')
    {
        push_stack(s, parse_type(p + k));
        k = strfind(p, ',');
    }
    return s;
}

int parse_def(struct token* tokens)
{
    if(tokens[0].type != TOKEN_DEF)
        return 0;
    #ifndef _DOLAR_VARS_
    if(tokens[1].value[0] == '$')
        error_func("Use of dollar sign variable");
    #endif
    return 0;
}

void set_error(int(*f)(const char*))
{
    error_func = f;
}

void parse_call(const char* str)
{
    char* p = strtok(str, " ");
    puts(p);
    if(p == NULL)
        return;
    #ifdef _MONITOR_
        printf("Calling %s\n", p);
    #endif
    void(*func)() = load_func(p);
    func();
}