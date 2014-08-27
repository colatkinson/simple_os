#pragma once
#include <sound.h>
#include <types.h>
#include <vga.h>
#include <utils.h>

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00

int bpm;
int32 init_music(int32 speed);
int32 play_note(float note, float duration);