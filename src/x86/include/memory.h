#pragma once
#include <types.h>

void *malloc(uint16 sz);
void free(void *ptr);

byte_t *heap;
byte_t *HeapCurEnd, *max_heap;
struct header *freelist;
extern int extmem;

#define HEAPSIG  0xDEADBEEF

void set_memory();

struct header
{
    uint32 sig;
    uint16 size;
    struct header *next;
};