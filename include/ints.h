#pragma once
#define SHORT(x) *(short*)&x
typedef unsigned char u8_t;
typedef unsigned int uint_t;

typedef struct {
    u8_t hi;
    u8_t low;
} u16_t;

typedef struct {
    u16_t hi;
    u16_t low;
} u32_t;

uint_t get_short(u16_t *p)
{
    return (p->hi << 8) | (p->low);
}

uint_t get_word(u32_t *p)
{
    return (get_short(&p->hi) << 16) | get_short(&p->low);
}