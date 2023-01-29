#include "parser.h"
#include <stdio.h>

int main()
{
    parse_stack("push 123", def_stk);
    struct Value i = pop_stack(def_stk);
    printf("%i", i.ptr);
    return 0;
}