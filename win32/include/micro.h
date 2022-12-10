// micro.h - (C)ord
// Header File for uControllers
#pragma once
#ifdef __GNUC__
#warning Use micro.h for microcontrollers only!
#endif
#include <stdint.h>
#define HIGH 1
#define LOW 0
#ifdef __arm__
void push_regs()
{
    asm("push {r0 - r15}");
}
#endif

void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);

struct regs
{
#ifdef __arm__
    int r0, r1, r2, r3, r4;
    int r5, r6, r7, r8, r9;
    int r10, r11, r12, r13, r14, r15;
    int psr;
#endif
};

void* __alloca(size_t sz);