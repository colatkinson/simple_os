#pragma once
#include <stddef.h> //we can use it: it doesnt use any platform-related api functions
#include <stdint.h> //include it to get int16_t and some integer types

typedef unsigned char byte_t;

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;

typedef uint8 bool;
#define true ((uint8)1)
#define false ((uint8)0)