#include <vga.h>

unsigned char g_640x480x16[] =
{
    /* MISC */
    0xE3,
    /* SEQ */
    0x03, 0x01, 0x08, 0x00, 0x06,
    /* CRTC */
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0B, 0x3E,
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xEA, 0x0C, 0xDF, 0x28, 0x00, 0xE7, 0x04, 0xE3,
    0xFF,
    /* GC */
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x05, 0x0F,
    0xFF,
    /* AC */
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x01, 0x00, 0x0F, 0x00, 0x00
};

byte_t BackBuffer;

unsigned get_fb_seg(void)
{
    unsigned seg;

    outportb(VGA_GC_INDEX, 6);
    seg = inportb(VGA_GC_DATA);
    seg >>= 2;
    seg &= 3;
    switch(seg)
    {
    case 0:
    case 1:
        seg = 0xA000;
        break;
    case 2:
        seg = 0xB000;
        break;
    case 3:
        seg = 0xB800;
        break;
    }
    return seg;
}

void vpokeb(unsigned off, unsigned val)
{
    pokeb(get_fb_seg(), off, val);
}

unsigned vpeekb(unsigned off)
{
    return peekb(get_fb_seg(), off);
}

void write_regs(unsigned char *regs)
{
    unsigned i;

    /* write MISCELLANEOUS reg */
    outportb(VGA_MISC_WRITE, *regs);
    regs++;
    /* write SEQUENCER regs */
    for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
    {
        outportb(VGA_SEQ_INDEX, i);
        outportb(VGA_SEQ_DATA, *regs);
        regs++;
    }
    /* unlock CRTC registers */
    outportb(VGA_CRTC_INDEX, 0x03);
    outportb(VGA_CRTC_DATA, inportb(VGA_CRTC_DATA) | 0x80);
    outportb(VGA_CRTC_INDEX, 0x11);
    outportb(VGA_CRTC_DATA, inportb(VGA_CRTC_DATA) & ~0x80);
    /* make sure they remain unlocked */
    regs[0x03] |= 0x80;
    regs[0x11] &= ~0x80;
    /* write CRTC regs */
    for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
    {
        outportb(VGA_CRTC_INDEX, i);
        outportb(VGA_CRTC_DATA, *regs);
        regs++;
    }
    /* write GRAPHICS CONTROLLER regs */
    for(i = 0; i < VGA_NUM_GC_REGS; i++)
    {
        outportb(VGA_GC_INDEX, i);
        outportb(VGA_GC_DATA, *regs);
        regs++;
    }
    /* write ATTRIBUTE CONTROLLER regs */
    for(i = 0; i < VGA_NUM_AC_REGS; i++)
    {
        (void)inportb(VGA_INSTAT_READ);
        outportb(VGA_AC_INDEX, i);
        outportb(VGA_AC_WRITE, *regs);
        regs++;
    }
    /* lock 16-color palette and unblank display */
    (void)inportb(VGA_INSTAT_READ);
    outportb(VGA_AC_INDEX, 0x20);
}

void set_plane(unsigned p)
{
    unsigned char pmask;

    p &= 3;
    pmask = 1 << p;
    /* set read plane */
    outportb(VGA_GC_INDEX, 4);
    outportb(VGA_GC_DATA, p);
    /* set write plane */
    outportb(VGA_SEQ_INDEX, 2);
    outportb(VGA_SEQ_DATA, pmask);
}

void write_pixel4p(unsigned x, unsigned y, unsigned c)
{
    unsigned wd_in_bytes, off, mask, p, pmask;

    wd_in_bytes = g_wd >> 3;
    off = wd_in_bytes * y + (x >> 3);
    x = x & 7;
    mask = 0x80 >> x;
    pmask = 1;
    for(p = 0; p < 4; p++)
    {
        set_plane(p);
        if(pmask & c)
        {
            pokeb(seg_val, off, peekb(seg_val, off) | mask);
        }
        else
        {
            pokeb(seg_val, off, peekb(seg_val, off) & ~mask);
        }
        pmask <<= 1;
    }
}

void drawchar(unsigned char c, int x, int y, int fgcolor, int bgcolor)
{
    int32 cx, cy;
    int32 mask[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    //unsigned char *glyph = ((unsigned char*)__font_bitmap__) + (int32)(c - 31) * 16;
    unsigned char *glyph = ((unsigned char*)__c64_bitmap__) + (int32)(c - 32) * 8;

    for(cy = 0; cy < 8; cy++)
    {
        for(cx = 0; cx < 8; cx++)
        {
            g_write_pixel(x - cx, y + cy - 6, glyph[cy]&mask[cx] ? fgcolor : bgcolor);
        }
    }
}

void vga_clear_screen() // clear the entire text screen
{
    outw(0x3c4, 0xff02);
    memset((void*)get_fb_seg(), BG, 640*480*3);
}

void vga_putchar(char c, int row, int col)
{
    drawchar(c, col * 8 + 8, row * 16 + 12, FG, BG);
}

uint32 vga_printf(char *message, uint32 line) // the message and then the line #
{
    int x = 0;
    while(*message != 0)
    {
        if(*message == '\n') // check for a new line char
        {
            line++;
            x = 0;
            *message++;
            continue;
        }

        if(x >= g_wd/8-1) // check if it would exceed screen width
        {
            line++;
            x = 0;
        }

        vga_putchar(*message, line, x);
        *message++;
        x++;
    }

    return line;
}

void init_graphics(void)
{
    write_regs(g_640x480x16);
    g_wd = 640;
    g_ht = 480;
    seg_val = get_fb_seg();
    g_write_pixel = write_pixel4p;

    vga_clear_screen();
}