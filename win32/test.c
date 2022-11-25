#include <stdio.h>
#ifdef _WIN32
#include <winmap.h>
char txt[] = "Global\\Process";

void test()
{
    puts("Wow");
}

int main()
{
    HANDLE c;
    LPVOID lpv;
    if(c = MapMemory(100, txt))
        lpv = ShareMemory(100, c);
    CpyFunction(lpv, test);
    UnmapViewOfFile(lpv);
    CloseHandle(c);
}
#endif