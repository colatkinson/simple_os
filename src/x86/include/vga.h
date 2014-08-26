#pragma once
#include <types.h>
#include <utils.h>
#include <u_vga16.h>

#define inportb(P)      inb(P)
#define outportb(P,V)       outb(P,V)

#define VGA_AC_INDEX        0x3C0
#define VGA_AC_WRITE        0x3C0
#define VGA_AC_READ     0x3C1
#define VGA_MISC_WRITE      0x3C2
#define VGA_SEQ_INDEX       0x3C4
#define VGA_SEQ_DATA        0x3C5
#define VGA_DAC_READ_INDEX  0x3C7
#define VGA_DAC_WRITE_INDEX 0x3C8
#define VGA_DAC_DATA        0x3C9
#define VGA_MISC_READ       0x3CC
#define VGA_GC_INDEX        0x3CE
#define VGA_GC_DATA         0x3CF
/*          COLOR emulation     MONO emulation */
#define VGA_CRTC_INDEX      0x3D4       /* 0x3B4 */
#define VGA_CRTC_DATA       0x3D5       /* 0x3B5 */
#define VGA_INSTAT_READ     0x3DA

#define VGA_NUM_SEQ_REGS    5
#define VGA_NUM_CRTC_REGS   25
#define VGA_NUM_GC_REGS     9
#define VGA_NUM_AC_REGS     21
#define VGA_NUM_REGS        (1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
                VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)

#define peekb(S,O)      *(unsigned char *)(16uL * (S) + (O))
#define pokeb(S,O,V)        *(unsigned char *)(16uL * (S) + (O)) = (V)

#define BG 9
#define FG 15

int32 g_wd;
int32 g_ht;

unsigned char g_320x200x4[];
unsigned char g_640x480x16[];
unsigned char g_320x200x256[];
unsigned char g_320x200x256_modex[];

void vpokeb(unsigned off, unsigned val);
unsigned vpeekb(unsigned off);

void write_regs(unsigned char *regs);
unsigned get_fb_seg(void);
void set_plane(unsigned p);
void write_pixel2(unsigned x, unsigned y, unsigned c);
void write_pixel4p(unsigned x, unsigned y, unsigned c);
void write_pixel8(unsigned x, unsigned y, unsigned c);
void write_pixel8x(unsigned x, unsigned y, unsigned c);
void (*g_write_pixel)(unsigned x, unsigned y, unsigned c);

void drawchar(unsigned char c, int x, int y, int fgcolor, int bgcolor);

void vga_clear_screen();
uint32 vga_printf(char *message, uint32 line);
void vga_putchar(char c, int row, int col);

void init_graphics(void);

byte_t BackBuffer;
