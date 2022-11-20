#ifndef __POSIX_VM__
#define __POSIX_VM__

#include <windows.h>

int execve(const char *pathname, char *const argv[],
           char *const envp[])
{
    return (int)ShellExecuteA(NULL, "open", (LPCSTR)pathname, (LPCSTR)argv, NULL, SW_NORMAL);
}

void open(char* name, char* x)
{
    
}

#endif // __POSIX_VM__