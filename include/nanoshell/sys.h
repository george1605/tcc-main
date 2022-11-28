#include <stdint.h>

typedef struct 
{
	uint32_t
		cr2,
		edi, esi, ebp, esp, ebx, edx, ecx, eax,
		error_code, 
		eip, cs, eflags;
}
Registers;

enum {
	LOGMSG = 1,
	MALLOC = 2,
	FREE   = 3,
	DUMPMEM= 4,
};

void OnSyscallReceived (Registers* pRegs);
