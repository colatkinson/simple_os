#pragma src

#include "types.h"
#include "vga.h"
#include "serial.h"
#include "char_table.h"
#include "sound.h"
#include "memory.h"

char * itoa( int value, char * str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

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
        if(inb(0x60) != c)
        {
            c = inb(0x60);
            if(c > 0 && c < sizeof(char_table))
            {
                if(char_table[c][0] != 0)
                {
                    if(char_table[c][0] == 127)
                    {
                        if(i > 0)
                        {
                            message[i] = 0;
                            i--;
                            message[i] = ' ';
                            vga_printf(message, line);
                        }
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
                        vga_printf(message, line);
                    }
                }
            }
        }
    }
    free(message);
}

void kernel_main()
{
    vga_clear_screen();
    char *intro_txt = " ____                  _         ___  ____  \n"
                      "/ ___| _ __ ___   ___ | | _____ / _ \\/ ___| \n"
                      "\\___ \\| '_ ` _ \\ / _ \\| |/ / _ \\ | | \\___ \\ \n"
                      " ___) | | | | | | (_) |   <  __/ |_| |___) |\n"
                      "|____/|_| |_| |_|\\___/|_|\\_\\___|\\___/|____/ \n"
                      "The OS for overweight cats";

    int line = vga_printf(intro_txt, 0);
    //COLOR = VGA_BLACK_BCK+VGA_WHITE_TXT;
    line = vga_printf(">install gentoo", line + 1);

    //COLOR = VGA_WHITE_BCK+VGA_BLUE_TXT;
    beep();
    kbd_loop(line + 1);
}

