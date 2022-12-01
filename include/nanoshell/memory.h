#ifndef __MEMORY_H__
#define __MEMORY_H__
#include <stdint.h>

#ifdef __KERNEL__ // only in kernel mode

#define KERNEL_BASE_ADDRESS (0xC0000000)
#define KERNEL_HEAP_BASE    (0x80000000)
#define USER_HEAP_BASE      (0x40000000)
#define PAGE_SIZE           (0x1000)

#define USER_EXEC_MAPPING_START    0x00C00000
#define USER_HEAP_DYNAMEM_START    0x40000000
#define KERNEL_HEAP_DYNAMEM_START  0x80000000
#define KERNEL_CODE_AND_DATA_START 0xC0000000
#define MMIO_AREA_0                0xD0000000
#define VBE_FRAMEBUFFER_HINT       0xE0000000
#define MMIO_AREA_1                0xF0000000
#define MMIO_VBOX_HINT         0xFF000000

#define PAGE_BIT_PRESENT      (0x1)
#define PAGE_BIT_READWRITE    (0x2)
#define PAGE_BIT_USERSUPER    (0x4)
#define PAGE_BIT_WRITETHRU    (0x8)
#define PAGE_BIT_CACHEDISABLE (0x10)
#define PAGE_BIT_ACCESSED     (0x20)

void MmFreePage(void* pAddr);
void* MmAllocateSinglePagePhyD(uint32_t* pPhysOut, const char* callFile, int callLine);
#define MmAllocateSinglePagePhy(physOut) MmAllocateSinglePagePhyD(physOut, __FILE__, __LINE__)

#endif

void* MmAllocateD (size_t size, const char* callFile, int callLine);
void* MmAllocateKD(size_t size, const char* callFile, int callLine);
#define MmAllocate(size)  MmAllocateD (size, __FILE__, __LINE__)
#define MmAllocateK(size) MmAllocateKD(size, __FILE__, __LINE__)

void* MmReAllocateD (void* old_ptr, size_t size, const char* callFile, int callLine);
void* MmReAllocateKD(void* old_ptr, size_t size, const char* callFile, int callLine);
#define MmReAllocate(old_ptr, size)  MmReAllocateD (old_ptr, size, __FILE__, __LINE__)
#define MmReAllocateK(old_ptr, size) MmReAllocateKD(old_ptr, size, __FILE__, __LINE__)

void MmFree (void* pAddr);
void MmFreeK(void* pAddr);
#endif