#define _MONITOR_
#include <stdlib.h>
#include "parser.h"

void parse(FILE* file)
{
    char* buf = malloc(100);
    struct token* tokens = alloc_tokens(50);
    size_t size = sizeof buf;
    while(getdelim(&buf, &size,'\n', file))
    {
        printf("%s\n", buf);
        get_tokens(buf, tokens);
        parse_def(tokens);
        memset((void*)tokens, 0, sizeof(struct token) * 50);
        memset(buf, 0, 100);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Format: interp <filename>");
        return -1;
    }
    FILE* fp = fopen(argv[1], "r");
    parse(fp);
    return 0;
}