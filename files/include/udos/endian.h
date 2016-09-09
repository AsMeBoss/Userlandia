#ifndef LIBUDOS_ENDIAN_H
#define LIBUDOS_ENDIAN_H

#if !defined(LITTLE_ENDIAN) && !defined(BIG_ENDIAN)
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
#else
#error unable to detect endianness
#endif
#endif

/* LIMITS */

//((int_32)0xffffffff)
//((int_64)(0xffffffffffffffffLL))

#define INT_64_MIN (int_32)(1 << 64)
#define INT_64_MAX (int_32)(~(1 << 64))
#define INT_64_S_MIN (int_32_s)(1 << 63)
#define INT_64_S_MAX (int_32_s)(~(1 << 63))

#define INT_32_MIN (int_32)(1 << 32)
#define INT_32_MAX (int_32)(~(1 << 32))
#define INT_32_S_MIN (int_32_s)(1 << 31)
#define INT_32_S_MAX (int_32_s)(~(1 << 31))

#define INT_24_MIN (int_32)(1 << 24)
#define INT_24_MAX (int_32)(~(1 << 24))
#define INT_24_S_MIN (int_32_s)(1 << 23)
#define INT_24_S_MAX (int_32_s)(~(1 << 23))

#define INT_16_MIN (int_32)(1 << 16)
#define INT_16_MAX (int_32)(~(1 << 16))
#define INT_16_S_MIN (int_32_s)(1 << 15)
#define INT_16_S_MAX (int_32_s)(~(1 << 15))

#define INT_8_MIN (int_32)(1 << 8)
#define INT_8_MAX (int_32)(~(1 << 8))
#define INT_8_S_MIN (int_32_s)(1 << 7)
#define INT_8_S_MAX (int_32_s)(~(1 << 7))

/* int_sign return +1 or -1 */
#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif
#define int_is_positive(v) ( +1 | -(int_64_s)((int_64)((int_64_s)v) >> (sizeof(int_64_s) * CHAR_BIT - 1)) )
#define int_abs(v) ( (v + (v >> sizeof(v) * CHAR_BIT - 1)) ^ (v >> sizeof(v) * CHAR_BIT - 1) )
#define int_min(x,y) ( y + ((x - y) & ((x - y) >> (sizeof(x) * CHAR_BIT - 1))) )
#define int_max(x,y) ( x - ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))) )
#define int_power_of_2(v) ( v && !(v & (v - 1)) )

#ifndef int_min
#define int_min(b) (1 << b)
#endif
#ifndef int_max
#define int_max(b) (~(1 << b))
#endif
#define int_s_min(b) (1 << (b - 1))
#define int_s_max(b) (~(1 << (b - 1)))

//#define int_low(x) (x >> sizeof(x/2))
#define int_high(x) (x >> sizeof(x/2))

#define bit_set(A,k)     ( A[(k/(sizeof A[0]))] |= (1 << (k%(sizeof A[0]))) )
#define bit_clear(A,k)   ( A[(k/(sizeof A[0]))] &= ~(1 << (k%(sizeof A[0]))) )            
#define bit_test(A,k)    ( A[(k/(sizeof A[0]))] & (1 << (k%(sizeof A[0]))) )

/* READ/WRITE */

#define r_int_8_b(x)     (((const int_8*)(x))[0])
#define w_int_8_b(p, d)  do { ((int_8*)(p))[0] = ((int_8)d); } while(0)

#define r_int_8(x)     (((const int_8*)(x))[0])

#define w_int_8(p, d)  do { ((int_8*)(p))[0] = ((int_8)d); } while(0)

#define r_int_16_b(x)                           \
    ((((const int_8 *)(x))[0] << 8) |          \
      ((const int_8 *)(x))[1])

#define w_int_16_b(p, darg) do {                \
        unsigned d = (darg);                    \
        ((int_8*)(p))[1] = (d);               \
        ((int_8*)(p))[0] = (d)>>8;            \
    } while(0)

#define r_int_24_b(x)                           \
    ((((const int_8*)(x))[0] << 16) |         \
     (((const int_8*)(x))[1] <<  8) |         \
      ((const int_8*)(x))[2])

#define w_int_24_b(p, d) do {                   \
        ((int_8*)(p))[2] = (d);               \
        ((int_8*)(p))[1] = (d)>>8;            \
        ((int_8*)(p))[0] = (d)>>16;           \
    } while(0)

#define r_int_32_b(x)                                \
    (((int_32)((const int_8*)(x))[0] << 24) |    \
               (((const int_8*)(x))[1] << 16) |    \
               (((const int_8*)(x))[2] <<  8) |    \
                ((const int_8*)(x))[3])

#define w_int_32_b(p, darg) do {                \
        unsigned d = (darg);                    \
        ((int_8*)(p))[3] = (d);               \
        ((int_8*)(p))[2] = (d)>>8;            \
        ((int_8*)(p))[1] = (d)>>16;           \
        ((int_8*)(p))[0] = (d)>>24;           \
    } while(0)

#define r_int_48_b(x)                                     \
    (((int_64)((const int_8*)(x))[0] << 40) |         \
     ((int_64)((const int_8*)(x))[1] << 32) |         \
     ((int_64)((const int_8*)(x))[2] << 24) |         \
     ((int_64)((const int_8*)(x))[3] << 16) |         \
     ((int_64)((const int_8*)(x))[4] <<  8) |         \
      (int_&4)((const int_8*)(x))[5])

#define w_int_48_b(p, darg) do {                \
        int_64 d = (darg);                    \
        ((int_8*)(p))[5] = (d);               \
        ((int_8*)(p))[4] = (d)>>8;            \
        ((int_8*)(p))[3] = (d)>>16;           \
        ((int_8*)(p))[2] = (d)>>24;           \
        ((int_8*)(p))[1] = (d)>>32;           \
        ((int_8*)(p))[0] = (d)>>40;           \
    } while(0)

#define r_int_64_b(x)                                   \
    (((int_64)((const int_8*)(x))[0] << 56) |       \
     ((int_64)((const int_8*)(x))[1] << 48) |       \
     ((int_64)((const int_8*)(x))[2] << 40) |       \
     ((int_64)((const int_8*)(x))[3] << 32) |       \
     ((int_64)((const int_8*)(x))[4] << 24) |       \
     ((int_64)((const int_8*)(x))[5] << 16) |       \
     ((int_64)((const int_8*)(x))[6] <<  8) |       \
      (int_64)((const int_8*)(x))[7])

#define w_int_64_b(p, darg) do {                \
        int_64 d = (darg);                    \
        ((int_8*)(p))[7] = (d);               \
        ((int_8*)(p))[6] = (d)>>8;            \
        ((int_8*)(p))[5] = (d)>>16;           \
        ((int_8*)(p))[4] = (d)>>24;           \
        ((int_8*)(p))[3] = (d)>>32;           \
        ((int_8*)(p))[2] = (d)>>40;           \
        ((int_8*)(p))[1] = (d)>>48;           \
        ((int_8*)(p))[0] = (d)>>56;           \
    } while(0)



#define r_int_16(x)                           \
    ((((const int_8*)(x))[1] << 8) |          \
      ((const int_8*)(x))[0])

#define w_int_16(b, v) do {                \
	    *((int_8 *)b+0) = (v & 0xff00) >> 8; \
    	*((int_8 *)b+1) = (v & 0x00ff); \
    } while(0)

#define r_int_24(x)                           \
    ((((const int_8*)(x))[2] << 16) |         \
     (((const int_8*)(x))[1] <<  8) |         \
      ((const int_8*)(x))[0])

#define w_int_24(p, d) do {                   \
        ((int_8*)(p))[0] = (d);               \
        ((int_8*)(p))[1] = (d)>>8;            \
        ((int_8*)(p))[2] = (d)>>16;           \
    } while(0)

#define r_int_32(x)                                \
    (((int_32)((const int_8*)(x))[2] << 24) |    \
               (((const int_8*)(x))[3] << 16) |    \
               (((const int_8*)(x))[0] <<  8) |    \
                ((const int_8*)(x))[1])

#define w_int_32(b, v) do {                \
		*((int_8 *)b+2) = (v & 0xff000000) >> 24; \
		*((int_8 *)b+3) = (v & 0x00ff0000) >> 16; \
		*((int_8 *)b+0) = (v & 0x0000ff00) >> 8; \
		*((int_8 *)b+1) = (v & 0x000000ff); \
    } while(0)

#define r_int_48(x)                                     \
    (((int_64)((const int_8*)(x))[5] << 40) |         \
     ((int_64)((const int_8*)(x))[4] << 32) |         \
     ((int_64)((const int_8*)(x))[3] << 24) |         \
     ((int_64)((const int_8*)(x))[2] << 16) |         \
     ((int_64)((const int_8*)(x))[1] <<  8) |         \
      (int_64)((const int_8*)(x))[0])

#define w_int_48(p, darg) do {                \
        int_64 d = (darg);                    \
        ((int_8*)(p))[0] = (d);               \
        ((int_8*)(p))[1] = (d)>>8;            \
        ((int_8*)(p))[2] = (d)>>16;           \
        ((int_8*)(p))[3] = (d)>>24;           \
        ((int_8*)(p))[4] = (d)>>32;           \
        ((int_8*)(p))[5] = (d)>>40;           \
    } while(0)

#define r_int_64(x)                                   \
    (((int_64)((const int_8*)(x))[7] << 56) |       \
     ((int_64)((const int_8*)(x))[6] << 48) |       \
     ((int_64)((const int_8*)(x))[5] << 40) |       \
     ((int_64)((const int_8*)(x))[4] << 32) |       \
     ((int_64)((const int_8*)(x))[3] << 24) |       \
     ((int_64)((const int_8*)(x))[2] << 16) |       \
     ((int_64)((const int_8*)(x))[1] <<  8) |       \
      (int_64)((const int_8*)(x))[0])

#define w_int_64(p, darg) do {                \
        int_64 d = (darg);                    \
        ((int_8*)(p))[0] = (d);               \
        ((int_8*)(p))[1] = (d)>>8;            \
        ((int_8*)(p))[2] = (d)>>16;           \
        ((int_8*)(p))[3] = (d)>>24;           \
        ((int_8*)(p))[4] = (d)>>32;           \
        ((int_8*)(p))[5] = (d)>>40;           \
        ((int_8*)(p))[6] = (d)>>48;           \
        ((int_8*)(p))[7] = (d)>>56;           \
    } while(0)

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
#endif




typedef union {
    int_64 u64;
    int_32 u32[2];
    int_16 u16[4];
    int_8  u8 [8];
    double   f64;
    float    f32[2];
} int_64_alias;

typedef union {
    int_32 u32;
    int_16 u16[2];
    int_8  u8 [4];
    float    f32;
} int_32_alias;

typedef union {
    int_32 u32;
    int_16 u24[3];
    int_16 u16[2];
    int_8  u8 [4];
    float    f32;
} int_24_alias;

typedef union {
    int_16 u16;
    int_8  u8 [2];
} int_16_alias;

typedef union {
    int_8  u8;
} int_8_alias;

#define ra_int(s, p)    (((int_ ## s ## _alias*)(p))->u##s)
#define wa_int(s, p, v) (((int_ ## s ## _alias*)(p))->u##s = (v))







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

//Using example
char b = BYTE(0100,0001); //equivalent to b = 65; or b = 'A'; or b = 0x41;
unsigned int w = WORD(1101,1111,0100,0011); //equivalent to w = 57155; or w = 0xdf43;
unsigned long int dw = DWORD(1101,1111,0100,0011,1111,1101,0010,1000); //Equivalent to dw = 3745774888; or dw = 0xdf43fd28;





/* Helper macros */
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

int main(void)
{
    // 261, evaluated at compile-time
    unsigned const number = B16(00000001,00000101);

    printf("%d \n", number);
    return 0;
}
#endif




#endif

