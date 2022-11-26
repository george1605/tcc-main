#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TYPE_INT 0x1
#define TYPE_FLOAT 0x2
#define TYPE_STRING 0x3

void read_raw(const char* file, const char* memory)
{
    FILE* fp = fopen(file, "r");
    fread(memory, 1, strlen(memory), fp);
}

void deserialise(int type, void* memory, char* buffer)
{
    switch(type)
    {
        case TYPE_INT:
            *(int*)memory = atoi(buffer);
        break;
        case TYPE_FLOAT:
            *(float*)memory = atof(buffer);
        break;
    }
}