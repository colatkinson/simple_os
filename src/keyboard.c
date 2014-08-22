#include <keyboard.h>

void kbd_loop(int32 line)
{
    char c = 0;
    char *message = (char *)malloc(20 * sizeof(char));
    int32 i = 0;
    int8 shift = 0;
    for (;;)
    {
        if(inb(0x60) != c)
        {
            c = inb(0x60);
            char buffer[20];
            itoa(c,buffer,10);   // here 2 means binary
            vga_printf(buffer, 0);
            if(c & 0x80)
            {
                if(c == -86)
                {
                    shift = 0;
                }
            }
            else
            {
                if(c == 42)
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
                        vga_printf(message, line);
                    }
                    else if(char_table[c][shift] == '\n')
                    {
                        line++;
                        message[0] = 0;
                        i = 0;
                    }
                    else
                    {
                        message[i] = char_table[c][shift];
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

/*char get_key()
{
    unsigned char key;
    unsigned char pressed;
    char c = 0;
    int i = 0;
    int j = 0;

    c = inb(0x60);
    if(c > 0)
            {
                if(char_table[c][0] != 0)
                {
                    if(char_table[c][0] == 127 && i > 0)
                    {
                        message[i] = 0;
                        i--;
                        message[i] = ' ';
                        vga_printf(message, line);
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
}*/