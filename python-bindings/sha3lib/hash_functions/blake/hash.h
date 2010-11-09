#ifndef HASH_H
#define HASH_H


#include <string.h>
#include <stdio.h>
#include <emmintrin.h>
#include <tmmintrin.h>

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned char u8; 

typedef struct  { 
  u32 h[8], s[4], t[2];
  int buflen, nullt;
  u8  buf[64];
} state;

static int blake32_compress( state * state, const u8 * datablock);
void blake32_init( state *S );
void blake32_update( state *S, const u8 *data, u64 datalen);
void blake32_final( state *S, u8 *digest);
int crypto_hash( unsigned char *out, const unsigned char *in , unsigned long long inlen);


#define U8TO32(p)					\
  (((u32)((p)[0]) << 24) | ((u32)((p)[1]) << 16) |	\
   ((u32)((p)[2]) <<  8) | ((u32)((p)[3])      ))
#define U32TO8(p, v)					\
  (p)[0] = (u8)((v) >> 24); (p)[1] = (u8)((v) >> 16);	\
  (p)[2] = (u8)((v) >>  8); (p)[3] = (u8)((v)      ); 


#endif
