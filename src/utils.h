#pragma once
//#include "liballoc.h"
//typedef unsigned long size_t;
typedef unsigned char byte_t;

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

byte_t *heap;
byte_t *HeapCurEnd, *max_heap;
struct header *freelist;
int extmem = 0;

void set_memory()
{
    heap = (byte_t *)0x100000;
    max_heap = heap + (extmem * 1024);
    freelist = NULL;
}

#define HEAPSIG  0xDEADBEEF

struct header
{
    unsigned int sig;
    size_t size;
    struct header *next;
};

void *malloc(size_t sz)
{
    if(!sz)
        return NULL;
    --sz;
    struct header *current = freelist;
    struct header *previous = freelist;
    while(current)
    {
        if(current->size > sz)
        {
            previous->next = current->next;
            if(current == freelist)
                freelist = current->next;
            current->next = NULL;
            return (void*) ++current;
        }
        previous = current;
        current = current->next;
    }
    ++sz;
    if(heap + sz + sizeof(struct header) > max_heap)
        return NULL;
    current = (struct header*)heap;
    current->sig = HEAPSIG;
    current->size = sz;
    current->next = NULL;
    heap += sz + sizeof(struct header);
    return (void*) ++current;
}

void free(void *ptr)
{
    struct header *hh = (struct header*)ptr;
    --hh;
    if(hh->sig != HEAPSIG)
        return;
    if(freelist == NULL)
        freelist = hh;
    else
    {
        hh->next = freelist->next;
        freelist->next = hh;
    }
}