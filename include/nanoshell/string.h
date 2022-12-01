#ifndef __STRING_H__
#define __STRING_H__
#include "main.h"

int memcmp(const void*ap,const void*bp,size_t size);
void* memcpy(void* dstptr, const void* srcptr, size_t size);// TODO: I don't think  we need restrict keyword here
void* memmove(void* restrict dstptr, const void* restrict srcptr, size_t size);
void* memset(void* bufptr, BYTE val, size_t size);
void memtolower(char* as, int w);
void memtoupper(char* as, int w);
void* fast_memset(void* bufptr, BYTE val, size_t size);

#endif
