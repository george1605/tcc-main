#include "parser.h"
#include <stdlib.h>

int main()
{
    struct Stack stk = alloc_stack(5);
    parse_stack("push 10", stk);
    printf("Hello: %i", stk.values[0].ptr);
    return 0;
}