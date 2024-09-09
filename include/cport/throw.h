#ifndef __THROW__
#define __THROW__
#include <stdlib.h>
#include <stdio.h>

#ifdef _SIGNAL_IMPL
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

#elif defined(_NOTIF_IMPL)
struct {
    char msg[100];
    int code;
    void(*handler)();
} notif;

// no error - default state
static void clr_notif()
{
    memset(notif.msg, 0, sizeof(notif.msg));
    notif.code = 0;
}

static int check_notif()
{
    return notif.code != 0;   
}

static void raise_notif()
{
    if(check_notif())
    {
        if(notif.handler != NULL)
            notif.handler();
        else {
            fprintf("Runtime Error: %s", notif.msg);
            exit(notif.code);
        }
    }
}

static void write_notif(const char* msg, int code)
{
    strncpy(notif.msg, msg, sizeof(notif.msg) - 1);
    notif.msg[sizeof(notif.msg) - 1] = '\0'; // Ensure null termination

    notif.code = code;

    raise_notif();
}

#define throw(msg, code) write_notif(msg, code)
#define throw_simple(msg) write_notif(msg, 1)
#define catch() notif.handler()

#endif
#endif