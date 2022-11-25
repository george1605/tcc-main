#pragma once
#include <winbase.h>
#include <dynlnk.h>
#define CHECK_WINSTD(func) (void*)func == (void*)(func ## A)
#define DLL_NAME(name) "Global\\Dll" ## name 

HANDLE MapMemory(size_t sz, LPCSTR szName)
{
    return CreateFileMappingA(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 sz,                // maximum object size (low-order DWORD)
                 szName);   
}

void* ShareMemory(size_t sz, HANDLE hMapFile)
{
    void* p = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                        FILE_MAP_ALL_ACCESS, // read/write permission
                        0,
                        0,
                        sz);
    if(p == NULL)
        CloseHandle(hMapFile);
    return p;
}

void CpyFunction(LPVOID memory, LPVOID function)
{
    char* mem = memory, *func = function;
    while(!strchr("\xc2\xc3\xca\xcb", *func))
        *mem++ = *func++;
    *mem = *func; // copies the RET instr
}