#pragma once
#include <malloc.h>
#define ADJACENCY(matrix, x) char matrix[x][x]

struct graf
{
    ADJACENCY(matrix, 10);
};

struct linked_list
{
    struct linked_list* next;
    #ifdef DOUBLE_LINKED
        struct linked_list* prev;
    #endif
};

struct queue
{
    void* ptr;
    size_t start, end;
};

struct stack
{
    void* ptr;
    size_t top;
};

struct tree
{
    int* fathers;
};

struct tree tree_alloc(size_t sz, int root)
{
    struct tree p;
    p.fathers = malloc(sz * 4);
    p.fathers[root] = 0;
}

void graph_addarc(struct graph* g, int from, int to)
{
    if(from == to)
        return;
    g->matrix[from][to] = 1;
}

void list_add(struct linked_list* head)
{
    head->next = malloc(sizeof(struct linked_list));
}