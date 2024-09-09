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

int parse_socket(const char* location, char* ip, int* port)
{
    if (location == NULL || ip == NULL || port == NULL) {
        return -1;
    }

    char loc_copy[32];  
    strncpy(loc_copy, location, sizeof(loc_copy) - 1);
    loc_copy[sizeof(loc_copy) - 1] = '\0';  // Ensure null termination

    char* _ip = strtok(loc_copy, ":");
    if (_ip == NULL) {
        *port = -1;
        return -1;
    }

    strncpy(ip, _ip, 255);
    ip[255] = '\0';  

    char* endptr;
    _ip = strtok(NULL, ":");
    if (_ip == NULL) {
        *port = -1;
        return -1;
    }

    long parsed_port = strtol(_ip, &endptr, 10);
    if (*endptr != '\0' || parsed_port < 0 || parsed_port > 65535) {
        *port = -1;
        return -1;
    }

    *port = (int)parsed_port;
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

void unsocket(SOCKFILE*);
void sclose(SOCKFILE*);

#ifdef __cplusplus
    }
#endif

#endif