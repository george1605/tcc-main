#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
char buf[101];

int main(int argc, char** argv)
{
    init_intrp();
    FILE* fp = fopen(argv[1], "r");
    if(!fp)
        return;
    int ok = !strcmp(argv[2], "-d");
    while(fgets(buf, 100, fp))
    {
        if(!strncmp(buf, "print", 5))
            parse_print(buf);
        if(!strncmp(buf, "call", 4))
            parse_call(buf);
        if(!strncmp(buf, "getkey", 6))
            parse_getkey(buf + 7);
        if(!strncmp(buf, "push", 4))
            parse_stack(buf, def_stk);
        memset(buf, 0, 100);
    }
    if(ok)
    {
        puts("Stack\n");
        while(def_stk.cnt)
        {
            struct Value p = pop_stack(def_stk);
            if(p.type == TYPE_STRING)
                puts(p.ptr);
            else
                printf("%i", p.ptr);
        }
    }
    fclose(fp); // be safe
    return 0;
}