#ifndef __STD_SOCK__
#define __STD_SOCK__

#ifdef __cplusplus
    extern "C" {
#endif

#include <malloc.h>
#include <string.h>
#include <stdlib.h>

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

int parse_socket(char* location, char* ip, int* port)
{
    if(ip == NULL || port == NULL) {
        return -1;
    }

    if(location == NULL) {
        *port = -1;
        return -1;
    }

    char* _ip = strtok(location, ":");
    if(_ip == NULL) {
        *port = -1;
        return -1;
    }

    strcpy(ip, _ip);
    char* wait;
    _ip = strtok(NULL, ":");
    *port = strtol(_ip, &wait, 10);
    if(*wait == '\0')
        return -1;
    return 0;
}

SOCKFILE* socket(int type);
SOCKFILE* sopen(char* location, int type); // sopen("192.168.10.10:800", )
void sconnect(SOCKFILE*, struct addrin_t);
struct addrin_t sinitaddr(int port, const char* ip);
int ssockopt(int reus, int flags);
int sbind(SOCKFILE* sf, struct addrin_t addr);
int ssend(SOCKFILE* file, char* msg, int size);
int ssrecv(SOCKFILE *file, char *buf, int size);
int slisten(SOCKFILE* file, int bklog);
int saccept(SOCKFILE* file, struct addrin_t* loc);

void unsocket(SOCKFILE*);

#ifdef __cplusplus
    }
#endif

#endif