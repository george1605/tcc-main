#include "parser.h"
#include <stdio.h>

int main()
{
    def_stk = alloc_stack(10);
    parse_math("15 * 7");
    printf("Result: %i", def_stk.values[0].ptr);
    return 0;
}