#include <vga.h>
#define RGB16( r, g, b ) ( ( r << 10 ) | ( g << 5 ) | ( b ) )

unsigned short colors[] = {
    RGB16(0, 0, 0),    //Black
    RGB16(0, 0, 16),   //Blue
    RGB16(0, 16, 0),   //Green
    RGB16(0, 16, 16),  //Cyan
    RGB16(16, 0, 0),   //Red
    RGB16(16, 0, 16),  //Magenta
    RGB16(16, 16, 0),  //Brown
    RGB16(24, 24, 24), //Light Grey
    RGB16(16, 16, 16), //Dark Grey
    RGB16(0, 0, 31),   //Light Blue
    RGB16(0, 31, 0),   //Light Green
    RGB16(0, 31, 31),  //Light Cyan
    RGB16(31, 0, 0),   //Light Red
    RGB16(31, 0, 31),  //Light Magenta
    RGB16(31, 31, 0),  //Yellow
    RGB16(31, 31, 31)  //White
};

void g_write_pixel(unsigned x, unsigned y, unsigned c)
{
    //((unsigned short*)0x06000000)[115+80*240] = 0x001F;
    /*((unsigned short*)0x06000000)[115+80*240] = RGB16(255, 0, 0);
    ((unsigned short*)0x06000000)[120+80*240] = 0x03E0;
    ((unsigned short*)0x06000000)[125+80*240] = 0x7C00;*/
    //((unsigned short*)0x06000000)[x+y*240] = RGB16(128, 128, 255);
    ((unsigned short*)0x06000000)[x+y*240] = RGB16(c*10, c*10, c*10);
}

void vga_clear_screen() // clear the entire text screen
{
    int i, j;
    for(i=0;i<240;i++)
    {
        for(j = 0;j<160;j++)
        {
            g_write_pixel(i, j, BG);
        }
    }
}

void init_graphics(void)
{
    *(unsigned int*)0x04000000 = 0x0403;
    g_wd = 240;
    g_ht = 160;

    vga_clear_screen();
}

char *a[] = {
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
    "........",
};

void drawchar(unsigned char c, int x, int y, int fgcolor, int bgcolor)
{
    int cx,cy;
    int mask[8]={1,2,4,8,16,32,64,128};
    unsigned char *glyph=((unsigned char*)__font_bitmap__)+(int)(c-31)*16;
 
    for(cy=0;cy<16;cy++){
        for(cx=0;cx<8;cx++){
            //if(glyph[cy]&mask[cx]) g_write_pixel(x-cx,y+cy-12,fgcolor);
            //g_write_pixel(x-cx, y+cy-12, glyph[cy]&mask[cx]?fgcolor:bgcolor);
            if(a[cy][cx]) g_write_pixel(x-cx,y+cy-12,fgcolor);
        }
    }
}

void vga_putchar(char c, int row, int col)
{
    drawchar(c, col*8+8, row*16+12, FG, BG);
}

uint32 vga_printf(char *message, uint32 line) // the message and then the line #
{
    int x = 0;
    while(*message != 0)
    {
        if(*message == '\n' || x>=g_wd) // check for a new line
        {
            line++;
            x = 0;
            *message++;
        }
        else
        {
            vga_putchar(*message, line, x);
            *message++;
            x++;
        }
    }

    return line;
}