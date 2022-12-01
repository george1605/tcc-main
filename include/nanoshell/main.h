#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define PATH_MAX (260)
typedef char byte;
typedef char BYTE;
typedef unsigned uint;


#ifdef __KERNEL__
#define asm __asm__ volatile

#define hlt __asm__ volatile("hlt\n\t")
#define cli __asm__ volatile("cli\n\t")
#define sti __asm__ volatile("sti\n\t")

extern void WritePort(unsigned short port, unsigned char data);
extern unsigned char ReadPort(unsigned short port);
extern void WritePortW(unsigned short port, unsigned short data);
extern unsigned short ReadPortW(unsigned short port);
extern void WritePortL(unsigned short port, unsigned int data);
extern unsigned int ReadPortL(unsigned int port);
#endif

#endif