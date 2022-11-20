#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define SYSCALL_OFFSET 0x20
#define SYSCALL(NAME) SYSCALL_OFFSET + NAME ## _CALL
#define REG(abstr, name) abstr->info.regs.name
typedef void*(*malloc_func)(size_t);
typedef void(*free_func)(void*);

enum SYSCALLS_NUM
{
    MALLOC_CALL,
    FREE_CALL,
    OPEN_CALL,
    WRITE_CALL,
    READ_CALL,
    CLOSE_CALL,
    SOCKET_CALL
};

struct TCCSysInfo
{
    uint32_t ram;
    uint64_t disk;
    struct {
        uint16_t w, h;
    } video;
    struct {
        uint8_t r0, r1, r2, r3, r4;
        uint16_t i0, i1, i2, i3, i4;
        uint32_t p0, p1;
    } regs;
};

struct TCCAbs
{
    void(*syscalls[16])();
    struct TCCSysInfo info; 
};

struct TCCVMAsm 
{
    char* bytes;
    size_t size;
};

static struct TCCAbs __abs;

void* debug_malloc(size_t p)
{
    if(p > __abs.info.ram)
        perror("Memory error: Cannot allocate a number of bytes higher than available");
    void* mem = malloc(p);
    if(mem == NULL)
        perror("Malloc failed: returned NULL");
    return mem;
}

void debug_free(void* ptr)
{
    if(ptr == NULL)
        perror("Cannot free NULL ptr");
    free(ptr);
}

void tcc_initvm(struct TCCAbs* abs)
{
    if(abs == NULL)
        return;
    #ifdef DEBUG
        abs->syscalls[0] = debug_malloc;
        abs->syscalls[1] = debug_free;
    #else
        abs->syscalls[0] = malloc;
        abs->syscalls[1] = free;
    #endif
}

void tcc_freevm(struct TCCAbs* abs)
{
    if(abs == NULL)
        return;
    memset(abs, 0, sizeof abs);
}

struct TCCVMAsm tcc_newasm(char* bytes)
{
    struct TCCVMAsm vasm;
    vasm.bytes = bytes;
    vasm.size = strlen(bytes);
    return vasm;
}

void tcc_execvm(struct TCCAbs* abs, struct TCCVMAsm vasm)
{
    if(abs == NULL)
        abs = &__abs;
    int i;
    for(i = 0;i < vasm.size;i++)
    {
        switch(vasm.bytes[i])
        {
        case SYSCALL(MALLOC):
            REG(abs, p0) = ((malloc_func)abs->syscalls[MALLOC_CALL])(REG(abs, i0));
        break;
        case SYSCALL(FREE):
            ((free_func)abs->syscalls[FREE_CALL])(REG(abs, p0));
        break;
        }
    }
}

void tcc_printregs(struct TCCAbs* abs)
{
    printf("p0=%u, p1=%u\n", REG(abs, p0), REG(abs, p1));
}

int main(int argc, char** argv)
{
    if(argc < 2)
        return -1;
    char* str = calloc(100, 1);
    FILE* p = fopen(argv[1], "rb");
    fread(str, 1, 100, p);
    tcc_execvm(&__abs, tcc_newasm(str));
    tcc_printregs(&__abs);
    return 0;
}