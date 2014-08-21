#include <vga.h>

char COLOR = VGA_BLUE_BCK + VGA_WHITE_TXT;

void vga_clear_screen() // clear the entire text screen
{
    char *vidmem = (char *) 0xb8000;
    uint32 i = 0;
    while(i < (VGA_WIDTH * VGA_HEIGHT * 2))
    {
        vidmem[i] = ' ';
        i++;
        vidmem[i] = COLOR;
        i++;
    };
};

void vga_clear_line(int line) // clear the entire text screen
{
    char *vidmem = (char *) 0xb8000;
    uint32 i = line * VGA_WIDTH * 2;
    while(i < (line + 1)*VGA_WIDTH * 2)
    {
        vidmem[i] = ' ';
        i++;
        vidmem[i] = COLOR;
        i++;
    };
};

uint16 make_vgaentry(char c, uint8 color)
{
    uint16 c16 = c;
    uint16 color16 = color;
    return c16 | color16 << 8;
}

void vga_putchar(char c, uint8 color, uint16 x, uint16 y)
{
    char *vidmem = (char *) 0xb8000;
    uint16 i = y * VGA_WIDTH + x;
    vidmem[i] = c;
    i++;
    vidmem[i] = color;
    i++;
}

uint32 vga_printf(char *message, uint32 line) // the message and then the line #
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