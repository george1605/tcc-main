#include "debug.h"

void p(int x)
{
    if(x == SIGSEGV)
        putc('\n', stdout);
}

int main()
{
    catch_errs(p); // p is the handler
    seterr {"Nothing", SIGSEGV};
    throw;
}