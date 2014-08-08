#pragma once
//#include "liballoc.h"
#include <stddef.h>
#include <stdint.h>
//typedef unsigned long size_t;
typedef unsigned char byte_t;

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

void delay_wait_short(unsigned int x);
void delay_wait (unsigned int x);