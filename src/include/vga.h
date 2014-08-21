#pragma once
#include <types.h>

#define WHITE_TXT 0x07 // white on black text
#define WHITE_BCK 0x70

static const uint16 VGA_WIDTH = 80;
static const uint16 VGA_HEIGHT = 25;

enum colors
{
    VGA_BLACK_TXT = 0x00,
    VGA_BLACK_BCK = 0x00,
    VGA_BLUE_TXT = 0x01,
    VGA_BLUE_BCK = 0x10,
    VGA_WHITE_TXT = 0x07,
    VGA_WHITE_BCK = 0x70,
};

void vga_clear_line(int32 line);
void vga_clear_screen();
uint32 vga_printf(char *message, uint32 line);
uint16 make_vgaentry(char c, uint8 color);

extern char COLOR;
