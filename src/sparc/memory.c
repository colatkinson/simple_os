#include <memory.h>

void set_memory()
{
    heap = (byte_t *)0x100000;
    max_heap = heap + (extmem * 1024);
    freelist = NULL;
}

void *malloc(uint16 sz)
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

void * memcpy ( void * destination, const void * source, size_t num )
{
    
}