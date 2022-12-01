#include "parser.h"
#include <stdio.h>

int main()
{
    struct Value val = parse_type("'A'");
    struct Value val2 = parse_type("false");
    printf("Char: %c, Bool: %i", (char)val.ptr, (char)val2.ptr);
    return 0;
}