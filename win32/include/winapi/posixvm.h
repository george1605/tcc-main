#ifndef __POSIX_VM__
#define __POSIX_VM__

#include <Windows.h>
#define O_RDONLY 0x0
#define O_WRONLY 0x1
#define O_RDWR 0x2

int execve(const char *pathname, char *const argv[],
           char *const envp[])
{
    return (int)ShellExecuteA(NULL, "open", (LPCSTR)pathname, (LPCSTR)argv, NULL, SW_NORMAL);
}

long open(char* name, int mode)
{
    OFSTRUCT of;
    return OpenFile(name, &of, mode);
}

void write(long fd, const char* data, size_t sz)
{
    DWORD p = 0;
    WriteFile((HANDLE)fd, &data, sz, &p, NULL);
}

void close(long handle)
{
    CloseHandle((HANDLE)handle);
}

#endif // __POSIX_VM__