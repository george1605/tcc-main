#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define SAVVY_BIN 0x10
#define X86_BIN 0x20
#define ARM_BIN 0x40
#define DEFAULT_BIN SAVVY_BIN

int binparse_args(int argc, char** argv)
{
    if(argc < 2)
        return DEFAULT_BIN;
    if(!strcmp(argv[1], "-x86"))
        return X86_BIN;
    if(!strcmp(argv[2], "-arm"))
        return ARM_BIN;
    return SAVVY_BIN;
}

void savvy_parse(const char* cmd, void* params, uint8_t* bytes)
{
    int c = 0;
    if(bytes == NULL)
        return;
    if(!strcmp(cmd, "malloc"))
        bytes[c++] = 0x20, bytes[c++] = *(int*)params;
    if(!strcmp(cmd, "free"))
    {
        bytes[c++] = 0x21;
        memcpy(bytes + c, &params, sizeof params); // params is the ptr 2b freed
    }
}

#define EAX_REG 0
#define ECX_REG 1
#define EBX_REG 2
#define EDX_REG 3
#define ESP_REG 4
#define EBP_REG 5

void x86_parse(const char* cmd, void* params, uint8_t* bytes)
{
    // TO DO!
    int c = 0;
    if(bytes == NULL)
        return;
    if(!strcmp(cmd, "ret"))
        bytes[c] = 0xc3;
    if(!strcmp(cmd, "mov"))
    {
        bytes[c] = 0xb8 + *(int*)params;
        bytes[c++] = ((int*)params)[1];
}