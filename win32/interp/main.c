#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
char buf[101];

void hello()
{
    puts("Hello!");
}

int main(int argc, char** argv)
{
    init_intrp();
    FILE* fp = fopen(argv[1], "r");
    export_func(hello, "hello");
    if(!fp)
        return;
    while(fgets(buf, 100, fp))
    {
        if(!strncmp(buf, "print", 5))
            parse_print(buf);
        if(!strncmp(buf, "call", 4))
            parse_call(buf);
        memset(buf, 0, 100);
    }
    fclose(fp); // be safe
    return 0;
}