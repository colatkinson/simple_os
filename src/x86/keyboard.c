#include <keyboard.h>

void kbd_loop(int32 line)
{
    //init_serial();
    unsigned char c = 0;
    char *message = (char *)malloc(20*sizeof(char));
    uint32 i = 0;
    int8 shift = 0;

    for (;;)
    {
        if(inb(0x60) != c)
        {
            c = inb(0x60);
            if(c & 0x80)
            {
                if(c == 0xAA)
                {
                    shift = 0;
                }
            }
            else
            {
                if(c == 0x2A)
                {
                    shift = 1;
                }
                if(char_table[c][shift] != 0)
                {
                    if(char_table[c][shift] == 127 && i > 0)
                    {
                        message[i] = 0;
                        i--;
                        message[i] = ' ';
                        //vga_printf(message, line);
                    }
                    else
                    {
                        message[i] = char_table[c][shift];
                        i++;
                        message[i] = 0;
                        //vga_printf(message, line);
                    }
                    //message[i] = 0;
                    //message[i+1] = 0;
                    vga_printf(message, line);
                }
            }
        }
            /*if(inb(0x60) != c && !(inb(0x60) & 0x80))
            {
                c = inb(0x60);
                if(char_table[c][0] != 0)
                {
                    message[i] = char_table[c][0];
                    i++;
                    message[i] = 0;
                    vga_putchar(char_table[c][0], line, x);
                    x++;
                }
                //vga_printf(message, line);
            }*/

        /*int j;
        for(j = 0; j < 20; j++)
        {
            if(message[j] == 0)
            {
                break;
            }
            write_serial('[');
            write_serial(message[j]);
            write_serial(']');
        }
        write_serial('\n');*/
        //delay_ms(33);
        //vga_iter();
    }
    free(message);
}