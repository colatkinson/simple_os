#pragma src
#define 	FHSB_HZ   FOSC0
#define 	FPBA_HZ   FOSC0
#define 	MEM_SPACE_SIZE   0x2000000
#define 	SDRAM_START_ADDRESS   0xD0000000

#include <stddef.h> //we can use it: it doesnt use any platform-related api functions
#include <stdint.h> //include it to get int16_t and some integer types
/*#include "liballoc_hooks.c"
#include "liballoc.h"
#include "utils.h"*/
#include "functions.h"
#include "serial.c"
#include "char_table.h"

void kbd_loop(int line)
{
    unsigned char key;
    unsigned char pressed;
    char c = 0;
    char *message = (char *)malloc(20 * sizeof(char));
    int i = 0;
    int j = 0;
    for (;;)
    {
        //key_decode(&key,&pressed);
        //k_putchar(key, VGA_BLACK_BCK+VGA_WHITE_TXT, 32, 32);
        if(inb(0x60) != c)
        {
            c = inb(0x60);
            if(c > 0)
            {
                //k_putchar(char_table[c][0], COLOR, 32, 32);
                if(char_table[c][0] != 0)
                {
                    if(char_table[c][0] == 127)
                    {
                        message[i] = 0;
                        i--;
                        message[i] = ' ';
                        k_printf(message, line);
                    }
                    else if(char_table[c][0] == '\n')
                    {
                        line++;
                        message[0] = 0;
                        i = 0;
                    }
                    else
                    {
                        message[i] = char_table[c][0];
                        i++;
                        message[i] = 0;
                        k_printf(message, line);
                    }
                }
            }
        }
    }
    free(message);
}

kernel_main()
{
    //pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
    //sdramc_init(FHSB_HZ);
    k_clear_screen();
    char *intro_txt = " ____                  _         ___  ____  \n"
                      "/ ___| _ __ ___   ___ | | _____ / _ \\/ ___| \n"
                      "\\___ \\| '_ ` _ \\ / _ \\| |/ / _ \\ | | \\___ \\ \n"
                      " ___) | | | | | | (_) |   <  __/ |_| |___) |\n"
                      "|____/|_| |_| |_|\\___/|_|\\_\\___|\\___/|____/ \n"
                      "The OS for overweight cats";

    int line = k_printf(intro_txt, 0);
//COLOR = VGA_BLACK_BCK+VGA_WHITE_TXT;
    line = k_printf(">install gentoo", line + 1);

//COLOR = VGA_WHITE_BCK+VGA_BLUE_TXT;
    kbd_loop(line + 1);
}
