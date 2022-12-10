// micro.h - Savvy Version
// Header File for uControllers
#pragma once
#ifdef __GNUC__
#warning Use micro.h for microcontrollers only!
#endif
#include <stdint.h>
#define HIGH 1
#define LOW 0
#define BIT(x) (1 << x)
#define BIT_SET(num, bit) num |= BIT(bit)
#define BIT_UNSET(num, bit) num &= ~BIT(bit)
#if defined(__arm__)
void push_regs()
{
    asm("push {r0 - r15}");
}
#elif defined(__avr__)
#include <avr/io.h>
#define SRAM_BEGIN 0x60
#define IO_BEGIN 0x20
#elif defined(__msp430__)
#include <msp430.h>
#endif

void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void analogWrite(int pin, int value);
int analogRead(int pin);

struct regs
{
#ifdef __arm__
    int r0, r1, r2, r3, r4;
    int r5, r6, r7, r8, r9;
    int r10, r11, r12, r13, r14, r15;
    int psr;
#endif
};

long clock();
void set_clock(long val);
void* __alloca(size_t sz);
void push_regs(struct regs* r);