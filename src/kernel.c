#include <types.h>
#include <vga.h>
#include <serial.h>
#include <char_table.h>
#include <sound.h>
#include <memory.h>
#include <keyboard.h>

void kernel_main()
{
    vga_clear_screen();
    char *intro_txt = " ____                  _         ___  ____  \n"
                      "/ ___| _ __ ___   ___ | | _____ / _ \\/ ___| \n"
                      "\\___ \\| '_ ` _ \\ / _ \\| |/ / _ \\ | | \\___ \\ \n"
                      " ___) | | | | | | (_) |   <  __/ |_| |___) |\n"
                      "|____/|_| |_| |_|\\___/|_|\\_\\___|\\___/|____/ \n"
                      "The OS for overweight cats";

    int32 line = vga_printf(intro_txt, 0);
    //COLOR = VGA_BLACK_BCK+VGA_WHITE_TXT;
    line = vga_printf(">install gentoo", line + 1);

    //COLOR = VGA_WHITE_BCK+VGA_BLUE_TXT;
    beep();
    kbd_loop(line + 1);
}

