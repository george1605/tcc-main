#pragma once
#include <malloc.h>
#include <stdio.h>
#include <signal.h>
#define DEFAULT_LOG "debug.log"

struct log
{
    FILE* __stdout;
    FILE* __stderr;
};

struct memblock {
        size_t size;
        void* ptr;
} __attribute__((packed));

struct meminfo
{
    struct memblock* blocks;
    size_t no_blocks;
    size_t freed;
};
static struct meminfo _meminfo;

void open_log(struct log* lg, const char* filename)
{
    if(!filename)
        filename = DEFAULT_LOG;
    lg->__stdout = freopen(filename, "w", stdout);
    lg->__stderr = freopen(filename, "w", stderr);
}

void close_log(struct log* lg)
{
    fclose(lg->__stderr);
    fclose(lg->__stdout);
}

void* __malloc(size_t sz)
{
    void* p = malloc(sz);
    struct memblock mb = {sz, p};
    _meminfo.blocks[++_meminfo.no_blocks] = mb;
    return p;
}

void catch_errs(void(*p)(int))
{
    signal(SIGSEGV, p);
    signal(SIGBREAK, p);
    signal(SIGABRT, p);
}