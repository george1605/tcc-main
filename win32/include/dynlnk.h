#include <malloc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BIN_ELF 0x1
#define BIN_EXE 0x2
#define BIN_OBJ 0x4
#define TEXT_SECTION ".text"
#define DATA_SECTION ".data"
#define RODATA_SECTION ".rodata"
#define BSS_SECTION ".bss"
#ifdef _WIN32
#define DLL_MAIN "DllMain"
#define WIN_MAIN "WinMain"
#define WWIN_MAIN "wWinMain"
#endif
typedef (*main_func)(int argc, char** argv);

uint8_t* relocate(const char* file, size_t size)
{
    FILE* fp = fopen(file, "rb");
    uint8_t* buffer = (uint8_t*)malloc(size + 1);
    fread(buffer, 1, size, fp);
    fclose(fp);
    return buffer;
}

size_t bintype(uint8_t* p)
{
    char b[] = {0x7f, 'E', 'L', 'F'};
    if(!strncmp(p, b, 4))
        return BIN_ELF;
    return INT32_MAX;
}

int execbytes(uint8_t* p)
{
    int(*func)() = p;
    return func();
}

char* find_symbol(uint8_t* buf, char* symbol)
{
    return strstr((const char*)buf, symbol);
}