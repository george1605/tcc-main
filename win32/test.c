#include <cport/new.h>
#include <stdio.h>

int when_bad(int s)
{
    puts("Caught bd alloc!");
}

int main()
{
    _catch(BADALLOC_ERR, when_bad);
    void* p = news(char, 100000000);
    printf("%p", p);
    delete(p);
}