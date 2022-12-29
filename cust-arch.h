#pragma once
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define STD_BIN "out.bin"

struct op
{
    char name[8];
    uint32_t code;
};

struct arch
{
    struct op* ops;
    size_t num, cap;
} _arch;

struct binary
{
    char* buffer; // small binaries
    FILE* fp;
    size_t sz;
};

void add_op(char* name, uint32_t code)
{
    if(_arch.cap <= _arch.num)
    {
        _arch.cap = _arch.num + 10;
        _arch.num++;
        _arch.ops = realloc(_arch.ops, sizeof(struct op) * _arch.cap);
        _arch.ops[_arch.num] = (struct op){name, code};
    } else {
        _arch.ops[++_arch.num] = (struct op){name, code};
    }
}

void alloc_arch()
{
    _arch.ops = malloc(sizeof(struct op) * 20);
    _arch.num = 0;
    _arch.cap = 20; 
}

void use_x86()
{
    alloc_arch();
    add_op("RET", 0xc3);
    add_op("ADD", 0xb8);
    // more ops
}

uint32_t get_opcode(char* cmd)
{
    for(int i = 1;i <= _arch.num;i++)
        if(!strcmp(_arch.ops[i].name, cmd))
            return _arch.ops[i].code;
}

void write_binary(struct binary* b)
{
    fwrite(b->buffer, 1, b->sz, b->fp);
}

struct binary* new_binary(const char* fname)
{
    if(!fname)
        fname = STD_BIN;
    struct binary* p = malloc(sizeof(struct binary));
    p->buffer = malloc(1024);
    p->sz = 1024;
    p->fp = fopen(fname, "w+");
    return p;
}