#include <sound.h>

//Play sound using built in speaker
void play_sound(uint32 nFrequence)
{
    uint64 Div;
    unsigned char tmp;

    //Set the PIT to the desired frequency
    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (unsigned char) (Div) );
    outb(0x42, (unsigned char) (Div >> 8));

    //And play the sound using the PC speaker
    tmp = inb(0x61);
    if (tmp != (tmp | 3))
    {
        outb(0x61, tmp | 3);
    }
}

//make it shutup
void nosound()
{
    unsigned char tmp = (inb(0x61) & 0xFC);

    outb(0x61, tmp);
}

//Make a beep
void beep()
{
    play_sound(2500);
    // wait for one second
    delay_ms(1000);
    nosound();
}