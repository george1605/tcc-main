#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define TYPE_INT 0x1
#define TYPE_FLOAT 0x2
#define TYPE_STRING 0x3
#define READ_STRUCT(file, str) read_raw(file, (char*)&str)
#define WRITE_STRUCT(file, str) write_raw(file, (char*)&str)

void read_raw(const char* file, const char* memory)
{
    FILE* fp = fopen(file, "r");
    fread((void*)memory, 1, strlen(memory), fp);
}

void write_raw(const char* file, const char* memory)
{
    FILE* fp = fopen(file, "w");
    fwrite(memory, 1, strlen(memory), fp);
}

void deserialise(int type, void* memory, char* buffer)
{
    if(memory == NULL || buffer == NULL)
        return;
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

// b is the pointer to last byte
void todec(int number, char* b)
{
    if (b == NULL || *b != '\0')  
        return;
    
    if (number == 0) {
        *b-- = '0';
        return;
    }

    while (number)
    {
        *b-- = (number % 10) + '0';  
        number /= 10;
    }
}

struct _float 
{
    uint8_t  sign      : 1;
    uint8_t  exponent  : 8;
    uint32_t mantissa  : 23;
};

void serialise(int type, void* memory, char* buffer)
{
 switch(type)
 {
    case TYPE_INT:
        todec(*(int*)memory, buffer);
    break;
    case TYPE_STRING:
        strcpy(buffer, (char*)memory);
    break;
    case TYPE_FLOAT:

    break;
 }   
}