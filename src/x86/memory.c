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

/*
memcpy
Copy count bytes from src to dest, and return dest.
*/
/*unsigned char *memcpy(unsigned const char *src, unsigned char *dest, int count)
{
    unsigned const char *src_pointer = (unsigned const char *)src;
    unsigned char *dest_pointer = (unsigned char *)dest;
    for(; count > 0; count--)
        *dest_pointer++ = *src_pointer++;
    return dest;
}*/
unsigned char *memcpy(unsigned const char *src, unsigned char *dest, size_t n) {
  uint32 num_dwords = n/4;
  uint32 num_bytes = n%4;
  uint32 *dest32 = (uint32*)dest;
  uint32 *src32 = (uint32*)src;
  uint8 *dest8 = ((uint8*)dest)+num_dwords*4;
  uint8 *src8 = ((uint8*)src)+num_dwords*4;
  uint32 i;

  for (i=0;i<num_dwords;i++) {
    dest32[i] = src32[i];
  }
  for (i=0;i<num_bytes;i++) {
    dest8[i] = src8[i];
  }
  return dest;
}

/*
memset
Set count bytes in dest to val, and return dest.
*/
unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    unsigned char *dest_pointer = (unsigned char *)dest;
    for(; count > 0; count--)
        *dest_pointer++ = val;
    return dest;
}

/*
memsetw
Set count bytes in dest to val, and return dest (but 16 bit this time).
*/
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *dest_pointer = (unsigned short *)dest;
    for(; count > 0; count--)
        *dest_pointer++ = val;
    return dest;
}