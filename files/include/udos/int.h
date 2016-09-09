#ifndef LIBUDOS_INT_H
#define LIBUDOS_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#define UNUSED(a) a = a

#if defined(__ia64__) || defined(__ia64) || defined(_M_IA64) || defined(_M_X64) || defined(_WIN64)
typedef unsigned long long int_pointer;
typedef signed long long int_pointer_s;
#elif defined(i386) || defined(__i386__) || defined(_X86_) || defined(_M_IX86) || defined(__INTEL__)
typedef unsigned long int_pointer;
typedef signed long int_pointer_s;
#else
typedef unsigned long int_pointer;
typedef signed long int_pointer_s;
#endif

typedef int_pointer sexpr;

typedef unsigned long long int_64;
typedef signed long long int_64_s;

typedef int_64 int_48;
typedef int_64_s int_48_s;

typedef unsigned int int_32;
typedef signed int int_32_s;

typedef int_32 int_24;
typedef int_32_s int_24_s;

typedef unsigned short int_16;
typedef signed short int_16_s;

typedef unsigned char int_8;
typedef signed char int_8_s;

typedef unsigned long long int_date;
typedef unsigned int int_time;

#ifdef _WIN32
typedef unsigned long int_pid;
typedef void * int_fd;
#else
typedef int_32_s int_pid;
typedef int_32_s int_fd;
#endif

typedef unsigned long int_size;

#ifndef __cplusplus
#if !defined(_STDBOOL_H)
    typedef _Bool bool;
    //typedef enum { false, true } bool;
    #define _STDBOOL_H
    #define true 0b1
    #define false 0b0
#endif
#endif

#ifdef __cplusplus
}
#endif

#include "udos/endian.h"

#endif
