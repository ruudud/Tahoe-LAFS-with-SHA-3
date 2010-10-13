#ifndef _FUGUE_T_H
#define _FUGUE_T_H

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

#ifdef __unix__
#define INLINE inline
#else
#define INLINE __inline
#endif

#if defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN
#define HO2BE_8(_x)  (_x)
#define HO2BE_4(_x)  (_x)
#else
#define HO2BE_8(_x)  ((_x<<56)|((_x<<40)&0xff000000000000ull)|((_x<<24)&0xff0000000000ull)|((_x<<8)&0xff00000000ull)|\
                     ((_x>>8)&0xff000000ull)|((_x>>24)&0xff0000ull)|((_x>>40)&0xff00ull)|(_x>>56))
#define HO2BE_4(_x)  ((_x<<24)|((_x<<8)&0xff0000)|((_x>>8)&0xff00)|(_x>>24))
#endif

#if defined(__WORDSIZE) && __WORDSIZE == 64
typedef unsigned long       uint64;
typedef unsigned int        uint32;
#else
typedef unsigned long long  uint64;
typedef unsigned long       uint32;
#endif
typedef unsigned short      uint16;
typedef unsigned char       uint8;

typedef union {
    uint32    d;
    uint8     b[4];
    }         hash32_s;
typedef hash32_s* hash32_p;

typedef struct {
    int        n;   /* columns in output */
    int        s;   /* columns in state */
    int        k;   /* number of smix's per TIX or round */
    int        r;   /* number of G1 rounds in final part */
    int        t;   /* number of G2 rounds in final part */
    }          hashCfg;

typedef struct {
    int        hashbitlen;
    hashCfg*   Cfg;
    int        Base;
    hash32_s   State[36];
    uint32     Partial[1];
    uint64     TotalBits;
    }          hashState;

#endif
