#ifndef __HOLY_C__
#define __HOLY_C__

// Tribute to Terry Davis
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <float.h>
#define Asm(x) asm(#x)
#define U0 void

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef char I8;
typedef short I16;
typedef int32_t I32;
typedef float F64;

// #ifdef __TEMPLE_OS__
#define MEM_PAG_BITS 9
#define MEM_PAG_SIZE (1 << MEM_PAG_BITS)
#define MEM_ADAM_STK (MEM_PAG_SIZE * 512) 
#define MEM_SETH_STK (MEM_PAG_SIZE * 512)
#define MEM_INTERRUPT_STK (MEM_PAG_SIZE * 512)
#define MEM_DFT_STK (MEM_PAG_SIZE * 512)

struct CDate
{
    U32 time;
    I32 date;
};

struct CFPU
{
    U8 body[512];
};

struct CMemBlk
{
    struct CMemBlk *next, *last;
    U32 mb_signature, pags;
};

U0* MAlloc (U32 size)
{
    return malloc(size);
}

U0 Free (U0* ptr)
{
    free(ptr);
}

U0 MemCpy (U0* dst, const U0* buf, U32 size)
{
    memcpy(dst, buf, size);
}

U0 MemSet (U0* ptr, U8 val, U32 size)
{
    memset(ptr, val, size);
}

// #endif // TEMPLE OS

#endif