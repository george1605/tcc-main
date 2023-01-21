#ifndef __STD_SOCK__
#define __STD_SOCK__

#ifdef __cplusplus
    extern "C" {
#endif

#include <malloc.h>
#ifdef _WIN32
#include <winsock.h>
#elif defined(__unix__)
#include <sys/socket.h>
#include <net/db.h>
#endif
#define SOCK_INET 0x10
#define SOCK_INTRN 0x20
#define S_REUSE 0x40
#define S_INET_REUSE SOCK_INET | S_REUSE

struct addrin_t {
    int family, addr, port;
};

typedef struct {
    void* _handle;
} SOCKFILE;

SOCKFILE* socket(int type);
void sconnect(SOCKFILE*, struct addrin_t);
struct addrin_t sinitaddr(int port, const char* ip);
int ssockopt(int reus, int flags);
int sbind(SOCKFILE* sf, struct addrin_t addr);
int ssend(SOCKFILE* file, char* msg, int size);
int ssrecv(SOCKFILE *file, char *buf, int size);

void unsocket(SOCKFILE*);

#ifdef __cplusplus
    }
#endif

#endif