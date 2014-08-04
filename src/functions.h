#pragma once

#define WHITE_TXT 0x07 // white on black text
#define WHITE_BCK 0x70

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

enum colors {
	VGA_BLACK_TXT = 0x00,
	VGA_BLACK_BCK = 0x00,
	VGA_BLUE_TXT = 0x01,
	VGA_BLUE_BCK = 0x10,
	VGA_WHITE_TXT = 0x0F,
	VGA_WHITE_BCK = 0xF0,
};

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);

char COLOR = VGA_BLUE_BCK+VGA_WHITE_TXT;

void k_clear_screen() // clear the entire text screen
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (VGA_WIDTH*VGA_HEIGHT*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=COLOR;
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
	unsigned int i=0;

	i=(line*VGA_WIDTH*2);

	while(*message!=0)
	{
		if(*message=='\n') // check for a new line
		{
			line++;
			i=(line*VGA_WIDTH*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=COLOR;
			i++;
		};
		line = i/(VGA_WIDTH*2);
	};

	return(line);
};
