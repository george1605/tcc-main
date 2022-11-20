#include <stdio.h>
#include <malloc.h>
#define DEFAULT_SIZE 100

void parseargs(char* string, char** args, size_t size)
{
    size_t i = 0, j = 0;
    while(string[i] && j < size)
    {
        if(string[i] == ' ')
            args[j++] = string + i;
        i++;
    }
}

char* prompt(char* question, size_t size)
{
    char* string = (char*)malloc(size);
    size_t i = 0;
    puts(question);
    fgets(string, size, stdin);
    return string;
}