#define X86_ARCH 1
#define ARM_ARCH 2
#define AVR_ARCH 4
#define RISC_ARCH 8

struct KernelInfo
{
    void* boot_ptr;
    void* kern_ptr;
    int arch;
} kern;

void main()
{
    if(kern.arch == X86_ARCH)
        asm("jmp %0":"r"(kern.boot_ptr));
    return 0;
}