#pragma once
#include <types.h>
//#include <string.h>

void *malloc(uint16 sz);
void free(void *ptr);

byte_t *heap;
byte_t *HeapCurEnd, *max_heap;
struct header *freelist;
extern int extmem;

#define HEAPSIG  0xDEADBEEF

void set_memory();

unsigned char *memcpy(unsigned const char *src, unsigned char *dest, size_t n);
unsigned char *memset(unsigned char *dest, unsigned char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

struct header
{
    uint32 sig;
    uint16 size;
    struct header *next;
};