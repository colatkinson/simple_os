#pragma once
#include <types.h>

uint8 inb(uint16 port);
void outb(uint16 port, uint8 val);

char * itoa(int32 value, char *str, int32 base);

void delay_wait_short(uint32 x);
void delay_wait (uint32 x);
void delay_ms (uint32 x);