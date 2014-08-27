#include <utils.h>

int extmem = 0;

uint8 inb(uint16 port)
{
    uint8 ret = 0;
    //asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

void outb(uint16 port, uint8 val)
{
    //asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

char * itoa(int32 value, char *str, int32 base)
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    }
    while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

void delay_wait_short (uint32 x)
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

void delay_wait (uint32 x)
{
    while (x > 30000)
    {
        x -= 30000;
        delay_wait_short(30000);
    };
    delay_wait_short(x);
};

void delay_ms (uint32 x)
{
    delay_wait(x * 1000000);
}