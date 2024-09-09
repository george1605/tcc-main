#ifndef __HOLY_C__
#define __HOLY_C__

// Tribute to Terry Davis
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <float.h>
#include <math.h>
#define Asm(x) asm(#x)
#define U0 void

#define _intern static
#define _extern extern

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef char I8;
typedef short I16;
typedef int32_t I32;
typedef float F32;
typedef double F64;

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

U8 GetC ()
{
    return fgetc(stdin);
}

F64 Floor(F64 d)
{
    return (int)d;
}

F64 Ceil(F64 d)
{
    return Floor(d) + 1;
}

F64 Sin(F64 d)
{
    return sin(d);
}

U0 SwapU8(U8* u1, U8* u2)
{
    if (u1 == NULL || u2 == NULL) {
        return;  // or handle error as needed
    }

    U8 aux = *u2;
    *u2 = *u1;
    *u1 = aux;
}

U0 SwapU816(U16* u1, U16* u2)
{
    if (u1 == NULL || u2 == NULL) {
        return;  // or handle error as needed
    }

    U16 aux = *u2;
    *u2 = *u1;
    *u1 = aux;
}

U0 SwapU8(U32* u1, U32* u2)
{
    if (u1 == NULL || u2 == NULL) {
        return;  // or handle error as needed
    }

    U32 aux = *u2;
    *u2 = *u1;
    *u1 = aux;
}

#ifdef _HOLY_C_GRAPHICS_
U0 PopUpOk(const U8* message);
#endif

// #endif // TEMPLE OS

#endif