#ifndef __THROW__
#define __THROW__
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

struct std_error
{
    char *msg;
    int code;
};

static struct std_error __error;
typedef void (*void_func_t)();
typedef void (*signal_func_t)(int);

void _try(void_func_t f, signal_func_t catc)
{
    int ret = (int)signal(SIGABRT, catc);
    if (!ret)
        puts("Unable to set signal handler!");
    f();
}

#define throws(error)              \
    {                              \
        fputs(error->msg, stderr); \
        raise(error->code);        \
    }
#define throw throws((&__error))
#define seterr __error = (struct std_error)
#define deferr { "Error!", 1 }
#define _catch(x, y) signal((int)x, y)
#endif