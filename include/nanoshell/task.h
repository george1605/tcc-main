#ifndef __TASK_H__
#define __TASK_H__

#define C_MAX_TASKS 1024
#define C_STACK_BYTES_PER_TASK 131072
struct __Task;
struct __Userheap;

typedef struct __UserHeap UserHeap;
typedef struct __Task Task;
typedef void (*TaskedFunction) (int arg);

#ifdef __KERNEL__
typedef struct CPUSaveState
{
	int ds,  es,  fs,  gs,  ss;
	int cr3;
	int eax, ebx, ecx, edx,
	    esi, edi, ebp, esp,
		eip, cs, eflags;
}
CPUSaveState;
#endif

typedef struct
{
	void *esp, *eax, *eip;
}
JumpBufferTag;

typedef JumpBufferTag JumpBuffer[1];
enum {
	TASK_SUCCESS = 0x10000000,
	TASK_ERROR_TOO_MANY_TASKS,
	TASK_ERROR_STACK_ALLOC_FAILED,
	TASK_ERROR_END,
};
#endif