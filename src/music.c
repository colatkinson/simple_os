#include <music.h>

int32 init_music(int32 speed)
{
    bpm = speed;
}

/*int32 play_note(float note, float duration)
{
    play_sound(note);

    /*char buffer[10];
    itoa((int)(60.0/bpm*1000.0*duration),buffer,10); // here 2 means binary
    vga_printf(buffer, 0);*

    delay_ms(60.0/bpm*1000.0*duration);
    nosound();
    delay_ms(1);

    return 0;
}*/
int32 play_note(float note, float duration) {}