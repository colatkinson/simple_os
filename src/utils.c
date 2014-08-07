#include "utils.h"

int extmem = 0;

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void set_memory()
{
     heap = (byte_t *)0x100000;
     max_heap = heap + (extmem * 1024);
     freelist = NULL;
}

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

void delay_wait_short (unsigned int x)
{
  unsigned short val;
  unsigned char lo, hi;

  val=x+20000;

  outb(32+16,0x43);
  outb(val&255,0x40);
  outb(val>>8,0x40);
  
  do outb(0xe2,0x43); while (inb(0x40)&64);

  for (;;) {
    outb(0,0x43);
    lo=inb(0x40);
    hi=inb(0x40);
    val=((unsigned short)lo) | (((unsigned short)hi) << 8);
    if (val<20000) break;
    //key_polling();
  };
};

void delay_wait (unsigned int x)
{
  while (x>30000) {
    x-=30000;
    delay_wait_short(30000);
  };
  delay_wait_short(x);
};