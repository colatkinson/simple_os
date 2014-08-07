#pragma once

#include <stddef.h>
#include <stdint.h>

#define WHITE_TXT 0x07 // white on black text
#define WHITE_BCK 0x70

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

enum colors
{
    VGA_BLACK_TXT = 0x00,
    VGA_BLACK_BCK = 0x00,
    VGA_BLUE_TXT = 0x01,
    VGA_BLUE_BCK = 0x10,
    VGA_WHITE_TXT = 0x07,
    VGA_WHITE_BCK = 0x70,
};

void k_clear_line(int line);
void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);
uint16_t make_vgaentry(char c, uint8_t color);

extern char COLOR;
