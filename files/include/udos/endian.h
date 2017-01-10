#ifndef LIBUDOS_ENDIAN_H
#define LIBUDOS_ENDIAN_H

#if !defined(LITTLE_ENDIAN)
#if defined(__BIG_ENDIAN__)
#define BIG_ENDIAN
#elif defined(__ARMEB__)
#define BIG_ENDIAN
#elif defined(__THUMBEB__)
#define BIG_ENDIAN
#elif defined(__AARCH64EB__)
#define BIG_ENDIAN
#elif defined(_MIPSEB)
#define BIG_ENDIAN
#elif defined(__MIPSEB)
#define BIG_ENDIAN
#elif defined(__MIPSEB__)
#define BIG_ENDIAN
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BIG_ENDIAN
#elif defined(_BIG_ENDIAN)
#define BIG_ENDIAN
#elif defined(__sparc)
#define BIG_ENDIAN
#elif defined(__sparc__)
#define BIG_ENDIAN
#elif defined(_POWER)
#define BIG_ENDIAN
#elif defined(__powerpc__)
#define BIG_ENDIAN
#elif defined(__ppc__)
#define BIG_ENDIAN
#elif defined(__hpux)
#define BIG_ENDIAN
#elif defined(__hppa)
#define BIG_ENDIAN
#elif defined(_POWER)
#define BIG_ENDIAN
#elif defined(__s390__)
#define BIG_ENDIAN
#elif defined(__LITTLE_ENDIAN__)
#define LITTLE_ENDIAN
#elif defined(__ARMEL__)
#define LITTLE_ENDIAN
#elif defined(__THUMBEL__)
#define LITTLE_ENDIAN
#elif defined(__AARCH64EL__)
#define LITTLE_ENDIAN
#elif defined(_MIPSEL)
#define LITTLE_ENDIAN
#elif defined(__MIPSEL)
#define LITTLE_ENDIAN
#elif defined(__MIPSEL__)
#define LITTLE_ENDIAN
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LITTLE_ENDIAN
#elif defined(_LITTLE_ENDIAN)
#define LITTLE_ENDIAN
#elif defined(__i386__)
#define LITTLE_ENDIAN
#elif defined(__alpha__)
#define LITTLE_ENDIAN
#elif defined(__ia64)
#define LITTLE_ENDIAN
#elif defined(__ia64__)
#define LITTLE_ENDIAN
#elif defined(_M_IX86)
#define LITTLE_ENDIAN
#elif defined(_M_IA64)
#define LITTLE_ENDIAN
#elif defined(_M_ALPHA)
#define LITTLE_ENDIAN
#elif defined(__amd64)
#define LITTLE_ENDIAN
#elif defined(__amd64__)
#define LITTLE_ENDIAN
#elif defined(_M_AMD64)
#define LITTLE_ENDIAN
#elif defined(__x86_64)
#define LITTLE_ENDIAN
#elif defined(__x86_64__)
#define LITTLE_ENDIAN
#elif defined(_M_X64)
#define LITTLE_ENDIAN
#elif defined(__bfin__)
#define LITTLE_ENDIAN

//((int_32)
//((int_64)

#define INT_64_MIN (int_32)(1 << 64)

#define INT_32_MIN (int_32)(1 << 32)

#define INT_24_MIN (int_32)(1 << 24)

#define INT_16_MIN (int_32)(1 << 16)

#define INT_8_MIN (int_32)(1 << 8)

/* int_sign return +1 or -1 */
#ifndef CHAR_BIT
#define CHAR_BIT
#define int_is_positive(v) 
#define int_abs(v)
#define int_min(x,y)
#define int_max(x,y) 
#define int_power_of_2(v) 

#ifndef int_min
#define int_min(b)
#ifndef int_max
#define int_max(b) 
#define int_s_min(b) 
#define int_s_max(b)

#define int_high(x) (x >> sizeof(x/2))

#define bit_set(A,k)     
#define bit_clear(A,k)             
#define bit_test(A,k)    

#define r_int_8_b(x)

#define r_int_16_b(x)                           \

#define r_int_24_b(x)                           \

#define w_int_24_b(p, d) 

#define r_int_32_b(x)  

#define w_int_32_b(p, darg)

#define r_int_48_b(x)

#define w_int_48_b(p, darg)

#define r_int_64_b(x)   

#define w_int_64_b(p, darg)

#define r_int_16(x)

#define w_int_16(b, v)

#define r_int_24(x)

#define w_int_24(p, d)

#define r_int_32(x)

#define w_int_32(b, v) 

#define r_int_48(x)  

#define w_int_48(p, darg)

#define r_int_64(x)

#define w_int_64(p, darg)

#ifdef BIG_ENDIAN
#   define r_int(s, p)      (int_##s)r_int_##s##_b(p)
#   define w_int(s, p, v)   w_int_##s##_b(p, v)
#   define r_int_b(s, p)    (int_##s)r_int_##s##_b(p)
#   define w_int_b(s, p, v) w_int_##s##_b(p, v)
#   define r_int_l(s, p)    (int_##s)r_int_##s(p)
#   define w_int_l(s, p, v) w_int_##s(p, v)
#else
#   define r_int(s, p)      (int_##s)r_int_##s(p)
#   define w_int(s, p, v)   w_int_##s((int_pointer)p, v)
#   define r_int_l(s, p)    (int_##s)r_int_##s(p)
#   define w_int_l(s, p, v) w_int_##s((int_pointer)p, v)
#   define r_int_b(s, p)    (int_##s)r_int_##s##_b(p)
#   define w_int_b(s, p, v) w_int_##s##_b((int_pointer)p, v)




typedef union {
    int_64 u64
}

typedef union {
    int_32 u32
}

typedef union {
    int_32 u32;
}

typedef union {
    int_16 u16
}

typedef union {
    int_8  u8
}







#if 0
#define B_0000  0
#define B_0001  1
#define B_0010  2
#define B_0011  3
#define B_0100  4
#define B_0101  5
#define B_0110  6
#define B_0111  7
#define B_1000  8
#define B_1001  9
#define B_1010  a
#define B_1011  b
#define B_1100  c
#define B_1101  d
#define B_1110  e
#define B_1111  f

#define _B2H(bits)  B_##bits
#define B2H(bits)   _B2H(bits)
#define _HEX(n)     0x##n
#define HEX(n)      _HEX(n)
#define _CCAT(a,b)  a##b
#define CCAT(a,b)   _CCAT(a,b)

#define BYTE(a,b)       HEX( CCAT(B2H(a),B2H(b)) )
#define WORD(a,b,c,d)   HEX( CCAT(CCAT(B2H(a),B2H(b)),CCAT(B2H(c),B2H(d))) )
#define DWORD(a,b,c,d,e,f,g,h)  HEX( CCAT(CCAT(CCAT(B2H(a),B2H(b)),CCAT(B2H(c),B2H(d))),CCAT(CCAT(B2H(e),B2H(f)),CCAT(B2H(g),B2H(h)))) )

char b = BYTE(0100,0001); //equivalent to b = 65; or b = 'A'; or b = 0x41;
unsigned int w = WORD(1101,1111,0100,0011); //equivalent to w = 57155; or w = 0xdf43;
unsigned long int dw = DWORD(1101,1111,0100,0011,1111,1101,0010,1000); //Equivalent to dw = 3745774888; or dw = 0xdf43fd28;


#define HEX__(n) 0x##n##LU
#define B8__(x) ((x&0x0000000FLU)?1:0) \
+((x&0x000000F0LU)?2:0) \
+((x&0x00000F00LU)?4:0) \
+((x&0x0000F000LU)?8:0) \
+((x&0x000F0000LU)?16:0) \
+((x&0x00F00000LU)?32:0) \
+((x&0x0F000000LU)?64:0) \
+((x&0xF0000000LU)?128:0)

/* User macros */
#define B8(d) ((unsigned char)B8__(HEX__(d)))
#define B16(dmsb,dlsb) (((unsigned short)B8(dmsb)<<8) \
+ B8(dlsb))
#define B32(dmsb,db2,db3,dlsb) (((unsigned long)B8(dmsb)<<24) \
+ ((unsigned long)B8(db2)<<16) \
+ ((unsigned long)B8(db3)<<8) \
+ B8(dlsb))


#include <stdio.h>
int main


