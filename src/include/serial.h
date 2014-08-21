#pragma once
#include <utils.h>
#include <types.h>
#define PORT 0x3f8

void init_serial();
int32 is_transmit_empty();
void write_serial(char a);