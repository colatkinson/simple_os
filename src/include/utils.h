#pragma once
//#include "liballoc.h"
#include <stddef.h>
#include <stdint.h>
//typedef unsigned long size_t;
typedef unsigned char byte_t;

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

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

void *malloc(size_t sz);
void free(void *ptr);