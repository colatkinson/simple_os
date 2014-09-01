#include <types.h>
#include <vga.h>
#include <serial.h>
#include <char_table.h>
#include <sound.h>
#include <memory.h>
#include <keyboard.h>
#include <music.h>
//#include <u_vga16.h>

//void kernel_main();

/*int main()
{
    /**(unsigned int*)0x04000000 = 0x0403;
 
    ((unsigned short*)0x06000000)[115+80*240] = 0x001F;
    ((unsigned short*)0x06000000)[120+80*240] = 0x03E0;
    ((unsigned short*)0x06000000)[125+80*240] = 0x7C00;*

    kernel_main();
 
    return 0;
}*/

//unsigned char *double_buffer;
//unsigned char *double_buffer = (unsigned char *) malloc(320*200);


/*static void demo_graphics(void)
{
    //printf("Screen-clear in 16-color mode will be VERY SLOW\n"
        //"Press a key to continue\n");
    //getch();
/* 4-color */
    /*write_regs(g_320x200x4);
    g_wd = 320;
    g_ht = 200;
    g_write_pixel = write_pixel2;*/
    //draw_x();
/* 16-color */
    /*write_regs(g_640x480x16);
    g_wd = 640;
    g_ht = 480;
    g_write_pixel = write_pixel4p;*/
    //draw_x();
    //g_write_pixel(100, 100, 1);
/* 256-color */
    /*write_regs(g_320x200x256);
    g_wd = 320;
    g_ht = 200;
    g_write_pixel = write_pixel8;
    //draw_x();*/
/* 256-color Mode-X */
    /*write_regs(g_320x200x256_modex);
    g_wd = 320;
    g_ht = 200;
    g_write_pixel = write_pixel8x;
    //draw_x();*/
//}

void kernel_main()
{
    //vga_clear_screen();
    char *intro_txt = " ____                  _         ___  ____  \n"
                      "/ ___| _ __ ___   ___ | | _____ / _ \\/ ___| \n"
                      "\\___ \\| '_ ` _ \\ / _ \\| |/ / _ \\ | | \\___ \\ \n"
                      " ___) | | | | | | (_) |   <  __/ |_| |___) |\n"
                      "|____/|_| |_| |_|\\___/|_|\\_\\___|\\___/|____/ \n"
                      "The OS for overweight cats";

    //int32 line = vga_printf(intro_txt, 0);
    //COLOR = VGA_BLACK_BCK+VGA_WHITE_TXT;
    //line = vga_printf(">install gentoo", line + 1);

    //beep();
    //kbd_loop(line + 1);
    //fillrect((unsigned char*)0xA0000, 0x4, 0x4, 0x4, 100, 100);
    //putpixel(0x4, 100, 100);
    //drawchar('A', 10, 10, 0x4, 0x0);
    //draw_char(__font_bitmap__);
    //demo_graphics();
    //memset(double_buffer, 0, 640*480);
    init_graphics();
    
    /*g_write_pixel(80, 80, 15);
    g_write_pixel(80, 81, 15);
    g_write_pixel(80, 82, 15);
    g_write_pixel(80, 83, 15);
    g_write_pixel(80, 84, 15);
    g_write_pixel(80, 85, 15);
    g_write_pixel(80, 86, 15);
    g_write_pixel(80, 87, 15);*/
    //drawchar('w', 100, 100, 9, 15);
    int32 line = vga_printf(intro_txt, 0);

    //memcpy(get_fb_seg(), double_buffer, 640*480*4);

    //memcpy(get_fb_seg(), double_buffer, 640*480*2);
    //memcpy(get_fb_seg(), double_buffer, 640*480);

    //beep();
    /*init_music(120);
    play_note(E4, 1.0);
    play_note(E4, 1);
    play_note(F4, 1);
    play_note(G4, 1);
    play_note(G4, 1);
    play_note(F4, 1);
    play_note(E4, 1);
    play_note(D4, 1);
    play_note(C4, 1);
    play_note(C4, 1);
    play_note(D4, 1);
    play_note(E4, 1);
    play_note(E4, 1.5);
    play_note(D4, 0.5);
    play_note(D4, 2);*/
    kbd_loop(line + 1);
    //g_write_pixel(100, 100, 1);*/

    while(true);
}
