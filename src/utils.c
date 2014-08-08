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

void delay_wait_short (unsigned int x)
{
    unsigned short val;
    unsigned char lo, hi;

    val = x + 20000;

    outb(32 + 16, 0x43);
    outb(val & 255, 0x40);
    outb(val >> 8, 0x40);

    do outb(0xe2, 0x43);
    while (inb(0x40) & 64);

    for (;;)
    {
        outb(0, 0x43);
        lo = inb(0x40);
        hi = inb(0x40);
        val = ((unsigned short)lo) | (((unsigned short)hi) << 8);
        if (val < 20000) break;
    };
};

void delay_wait (unsigned int x)
{
    while (x > 30000)
    {
        x -= 30000;
        delay_wait_short(30000);
    };
    delay_wait_short(x);
};

delay_ms (unsigned int x)
{
    delay_wait(x * 1000000);
}