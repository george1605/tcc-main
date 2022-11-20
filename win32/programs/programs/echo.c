#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        puts("Format: echo <opts> <string>");
        return 0;
    }
    
    if(!strcmp(argv[1], "-n") && argc >= 3)
    {
        int p;
        for(p = 0;argv[2][p] != NULL;p++)
            if(argv[2][p] == '\\')
                { continue; }
            else
                putc(argv[2][p], stdout);
        return 0;
    }
    for(int i = 1;i < argc;i++)
        printf("%s ", argv[i]);
    return 0;
}