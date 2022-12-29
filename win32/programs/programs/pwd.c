#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#elif defined(__unix__)
#include <unistd.h>
#endif

int main()
{
    char buf[101];
    #ifdef _WIN32
        GetCurrentDirectoryA(100, buf);
    #elif defined(__unix__)
        getcwd(buf, 100);
    #endif
    printf("%s", buf);
    return 0;
}