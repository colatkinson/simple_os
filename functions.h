//////////////////////////////////////////////
// This code was made for the tutorial:
// "Making a Simple C kernel with Basic printf and clearscreen Functions"
//
// This code comes with absolutly
// NO WARRANTY
// you can not hold me(KJ), nor
// anyone else responsible for what
// this code does.
//
// This code is in the public domain,
// you may use it however you want
//////////////////////////////////////////////

#pragma once

#define WHITE_TXT 0x07 // white on black text
#define WHITE_BCK 0x70

static const size_t VGA_WIDTH = 160;
static const size_t VGA_HEIGHT = 50;

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

char color = VGA_BLUE_BCK+VGA_WHITE_TXT;

k_main() // like main in a normal C program
{
	k_clear_screen();
	k_printf("Hi!\nHow's this for a starter OS?", 0);
};

void k_clear_screen() // clear the entire text screen
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (VGA_WIDTH*VGA_HEIGHT*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=color;
		i++;
	};
};

unsigned int k_printf(char *message, unsigned int line) // the message and then the line #
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*VGA_WIDTH);

	while(*message!=0)
	{
		if(*message=='\n') // check for a new line
		{
			line++;
			i=(line*VGA_WIDTH);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=color;
			i++;
		};
	};

	return(line);
};
