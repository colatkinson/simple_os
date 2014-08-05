#include "functions.h"

char COLOR = VGA_BLUE_BCK + VGA_WHITE_TXT;

void k_clear_screen() // clear the entire text screen
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = 0;
    while(i < (VGA_WIDTH * VGA_HEIGHT * 2))
    {
        vidmem[i] = ' ';
        i++;
        vidmem[i] = COLOR;
        i++;
    };
};

void k_clear_line(int line) // clear the entire text screen
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = line * VGA_WIDTH * 2;
    while(i < (line + 1)*VGA_WIDTH * 2)
    {
        vidmem[i] = ' ';
        i++;
        vidmem[i] = COLOR;
        i++;
    };
};

uint16_t make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

unsigned int k_putchar(char c, uint8_t color, size_t x, size_t y)
{
    char *vidmem = (char *) 0xb8000;
    size_t i = y * VGA_WIDTH + x;
    vidmem[i] = c;
    i++;
    vidmem[i] = color;
    i++;
}

unsigned int k_printf(char *message, unsigned int line) // the message and then the line #
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = 0;

    i = (line * VGA_WIDTH * 2);

    while(*message != 0)
    {
        if(*message == '\n') // check for a new line
        {
            line++;
            i = (line * VGA_WIDTH * 2);
            *message++;
        }
        else
        {
            vidmem[i] = *message;
            *message++;
            i++;
            vidmem[i] = COLOR;
            i++;
        };
        line = i / (VGA_WIDTH * 2);
    };

    return(line);
};

/*void k_print_dec(u32int n)
{

    if (n == 0)
    {
        k_putchar('0', 0, 0);
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    monitor_write(c2);

}*/