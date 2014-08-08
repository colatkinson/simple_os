#pragma once
#include <stddef.h>
#include <stdint.h>
typedef unsigned char byte_t;

void *malloc(size_t sz);
void free(void *ptr);

byte_t *heap;
byte_t *HeapCurEnd, *max_heap;
struct header *freelist;
extern int extmem;

#define HEAPSIG  0xDEADBEEF

void set_memory();

struct header
{
    unsigned int sig;
    size_t size;
    struct header *next;
};