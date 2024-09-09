#pragma once
#include <stddef.h>
#define SHORT(x) *(short*)&x
typedef unsigned char u8_t;

typedef struct {
    u8_t x[2];
} uint16_u;

typedef struct {
    u8_t x[4];
} uint32_u;

void swap_endian16(uint16_u* str)
{
    if(str == NULL) return;

    u8_t aux = str->x[1];
    str->x[1] = str->x[0];
    str->x[0] = aux;
}

void swap_endian32(uint32_u* str)
{
    if(str == NULL) return;

    u8_t aux;

    aux = str->x[3];
    str->x[3] = str->x[0];
    str->x[0] = aux;

    aux = str->x[2];
    str->x[2] = str->x[1];
    str->x[1] = aux;
}