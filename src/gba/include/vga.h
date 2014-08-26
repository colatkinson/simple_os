#pragma once
#include <types.h>
#include <u_vga16.h>

#define BG 9
#define FG 15

int32 g_wd;
int32 g_ht;

void init_graphics(void);
void g_write_pixel(unsigned x, unsigned y, unsigned c);
void vga_clear_screen();
uint32 vga_printf(char *message, uint32 line);
void drawchar(unsigned char c, int x, int y, int fgcolor, int bgcolor);