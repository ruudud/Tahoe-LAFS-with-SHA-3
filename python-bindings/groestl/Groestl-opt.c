/* Groestl-opt.c     October 2008
 * ANSI C code optimised for 32-bit machines
 * Authors: Soeren S. Thomsen
 *          Krystian Matusiewicz
 *
 * This code is placed in the public domain
 */

#include "Groestl-opt.h"
#include "tables.h"

/* compute one new state column */
#define COLUMN(x,y,i,a,b,c,d,e,f,g,h,r0,r4,r3,r7) y[i] =	\
    T[0*256+((r0)^EXT_BYTE(x[a], 0))]^				\
    T[1*256+      EXT_BYTE(x[b], 1) ]^				\
    T[2*256+      EXT_BYTE(x[c], 2) ]^				\
    T[3*256+((r3)^EXT_BYTE(x[d], 3))]^				\
    T[4*256+((r4)^EXT_BYTE(x[e], 0))]^				\
    T[5*256+      EXT_BYTE(x[f], 1) ]^				\
    T[6*256+      EXT_BYTE(x[g], 2) ]^				\
    T[7*256+((r7)^EXT_BYTE(x[h], 3))]

/* compute lower part of state (short variants) */
void RND512L(const u32 *x, u32 *y, int r, int s) {
  COLUMN(x,y, 1, 9,11,13,15, 0, 2, 4, 6,0,r,0,0);
  COLUMN(x,y, 3,11,13,15, 1, 2, 4, 6, 8,0,0,s,0);
  COLUMN(x,y, 5,13,15, 1, 3, 4, 6, 8,10,0,0,0,0);
  COLUMN(x,y, 7,15, 1, 3, 5, 6, 8,10,12,0,0,0,0);
  COLUMN(x,y, 9, 1, 3, 5, 7, 8,10,12,14,0,0,0,0);
  COLUMN(x,y,11, 3, 5, 7, 9,10,12,14, 0,0,0,0,0);
  COLUMN(x,y,13, 5, 7, 9,11,12,14, 0, 2,0,0,0,0);
  COLUMN(x,y,15, 7, 9,11,13,14, 0, 2, 4,0,0,0,0);
}

/* compute a round in P or Q (short variants) */
#define RND512(x, y, r, s) do {				\
    COLUMN(x,y, 0, 0, 2, 4, 6, 9,11,13,15,r,0,0,0);	\
    COLUMN(x,y, 2, 2, 4, 6, 8,11,13,15, 1,0,0,0,s);	\
    COLUMN(x,y, 4, 4, 6, 8,10,13,15, 1, 3,0,0,0,0);	\
    COLUMN(x,y, 6, 6, 8,10,12,15, 1, 3, 5,0,0,0,0);	\
    COLUMN(x,y, 8, 8,10,12,14, 1, 3, 5, 7,0,0,0,0);	\
    COLUMN(x,y,10,10,12,14, 0, 3, 5, 7, 9,0,0,0,0);	\
    COLUMN(x,y,12,12,14, 0, 2, 5, 7, 9,11,0,0,0,0);	\
    COLUMN(x,y,14,14, 0, 2, 4, 7, 9,11,13,0,0,0,0);	\
    RND512L(x,y,r,s);					\
  } while (0)

/* compute lower part of state (long variants) */
void RND1024(const u32 *x, u32 *y, int r, int s) {
  COLUMN(x,y, 0, 0, 2, 4, 6, 9,11,13,23,r,0,0,0);
  COLUMN(x,y, 2, 2, 4, 6, 8,11,13,15,25,0,0,0,0);
  COLUMN(x,y, 4, 4, 6, 8,10,13,15,17,27,0,0,0,0);
  COLUMN(x,y, 6, 6, 8,10,12,15,17,19,29,0,0,0,0);
  COLUMN(x,y, 8, 8,10,12,14,17,19,21,31,0,0,0,0);
  COLUMN(x,y,10,10,12,14,16,19,21,23, 1,0,0,0,s);
  COLUMN(x,y,12,12,14,16,18,21,23,25, 3,0,0,0,0);
  COLUMN(x,y,14,14,16,18,20,23,25,27, 5,0,0,0,0);
  COLUMN(x,y,16,16,18,20,22,25,27,29, 7,0,0,0,0);
  COLUMN(x,y,18,18,20,22,24,27,29,31, 9,0,0,0,0);
  COLUMN(x,y,20,20,22,24,26,29,31, 1,11,0,0,0,0);
  COLUMN(x,y,22,22,24,26,28,31, 1, 3,13,0,0,0,0);
  COLUMN(x,y,24,24,26,28,30, 1, 3, 5,15,0,0,0,0);
  COLUMN(x,y,26,26,28,30, 0, 3, 5, 7,17,0,0,0,0);
  COLUMN(x,y,28,28,30, 0, 2, 5, 7, 9,19,0,0,0,0);
  COLUMN(x,y,30,30, 0, 2, 4, 7, 9,11,21,0,0,0,0);

  COLUMN(x,y, 1, 9,11,13,23, 0, 2, 4, 6,0,r,0,0);
  COLUMN(x,y, 3,11,13,15,25, 2, 4, 6, 8,0,0,0,0);
  COLUMN(x,y, 5,13,15,17,27, 4, 6, 8,10,0,0,0,0);
  COLUMN(x,y, 7,15,17,19,29, 6, 8,10,12,0,0,0,0);
  COLUMN(x,y, 9,17,19,21,31, 8,10,12,14,0,0,0,0);
  COLUMN(x,y,11,19,21,23, 1,10,12,14,16,0,0,s,0);
  COLUMN(x,y,13,21,23,25, 3,12,14,16,18,0,0,0,0);
  COLUMN(x,y,15,23,25,27, 5,14,16,18,20,0,0,0,0);
  COLUMN(x,y,17,25,27,29, 7,16,18,20,22,0,0,0,0);
  COLUMN(x,y,19,27,29,31, 9,18,20,22,24,0,0,0,0);
  COLUMN(x,y,21,29,31, 1,11,20,22,24,26,0,0,0,0);
  COLUMN(x,y,23,31, 1, 3,13,22,24,26,28,0,0,0,0);
  COLUMN(x,y,25, 1, 3, 5,15,24,26,28,30,0,0,0,0);
  COLUMN(x,y,27, 3, 5, 7,17,26,28,30, 0,0,0,0,0);
  COLUMN(x,y,29, 5, 7, 9,19,28,30, 0, 2,0,0,0,0);
  COLUMN(x,y,31, 7, 9,11,21,30, 0, 2, 4,0,0,0,0);
}


/* compute compression function (short variants) */
void F512(u32 *h, const u32 *m) {
  int i;
  u32 Ptmp[2*COLS512];
  u32 Qtmp[2*COLS512];
  u32 y[2*COLS512];
  u32 z[2*COLS512];

  for (i = 0; i < 2*COLS512; i++) {
    Ptmp[i] = h[i]^m[i];
  }

  /* compute Q(m) */
  RND512(m, y, 0, 0xff^0);
  RND512(y, z, 0, 0xff^1);
  RND512(z, y, 0, 0xff^2);
  RND512(y, z, 0, 0xff^3);
  RND512(z, y, 0, 0xff^4);
  RND512(y, z, 0, 0xff^5);
  RND512(z, y, 0, 0xff^6);
  RND512(y, z, 0, 0xff^7);
  RND512(z, y, 0, 0xff^8);
  RND512(y, Qtmp, 0, 0xff^9);

  /* compute P(h+m) */
  RND512(Ptmp, y, 0, 0);
  RND512(y, z, 1, 0);
  RND512(z, y, 2, 0);
  RND512(y, z, 3, 0);
  RND512(z, y, 4, 0);
  RND512(y, z, 5, 0);
  RND512(z, y, 6, 0);
  RND512(y, z, 7, 0);
  RND512(z, y, 8, 0);
  RND512(y, Ptmp, 9, 0);

  /* compute P(h+m) + Q(m) + h */
  for (i = 0; i < 2*COLS512; i++) {
    h[i] ^= Ptmp[i]^Qtmp[i];
  }
}

/* compute compression function (long variants) */
void F1024(u32 *h, const u32 *m) {
  int i;
  u32 Ptmp[2*COLS1024];
  u32 Qtmp[2*COLS1024];
  u32 y[2*COLS1024];
  u32 z[2*COLS1024];

  for (i = 0; i < 2*COLS1024; i++) {
    Ptmp[i] = h[i]^m[i];
  }

  /* compute Q(m) */
  RND1024(m, y, 0, 0xff^0);
  RND1024(y, z, 0, 0xff^1);
  RND1024(z, y, 0, 0xff^2);
  RND1024(y, z, 0, 0xff^3);
  RND1024(z, y, 0, 0xff^4);
  RND1024(y, z, 0, 0xff^5);
  RND1024(z, y, 0, 0xff^6);
  RND1024(y, z, 0, 0xff^7);
  RND1024(z, y, 0, 0xff^8);
  RND1024(y, z, 0, 0xff^9);
  RND1024(z, y, 0, 0xff^10);
  RND1024(y, z, 0, 0xff^11);
  RND1024(z, y, 0, 0xff^12);
  RND1024(y, Qtmp, 0, 0xff^13);

  /* compute P(h+m) */
  RND1024(Ptmp,y,0,0);
  for (i = 1; i < ROUNDS1024-1; i += 2) {
    RND1024(y,z,i,0);
    RND1024(z,y,i+1,0);
  }
  RND1024(y,Ptmp,ROUNDS1024-1,0);

  /* compute P(h+m) + Q(m) + h */
  for (i = 0; i < 2*COLS1024; i++) {
    h[i] ^= Ptmp[i]^Qtmp[i];
  }
}


/* digest up to msglen bytes of input (full blocks only) */
void Transform(hashState *ctx, 
	       const u8 *input, 
	       int msglen) {
  /* determine variant, SHORT or LONG, and select underlying
     compression function based on the variant */
  void (*F)(u32*,const u32*);
  switch ( ctx->v ) {
  case SHORT : F = &F512; break;
  case LONG  : 
  default    : F = &F1024; break;
  }

  /* digest message, one block at a time */
  for (; msglen >= ctx->statesize; 
       msglen -= ctx->statesize, input += ctx->statesize) {
    F(ctx->chaining,(u32*)input);

    /* increment block counter */
    ctx->block_counter1++;
    if (ctx->block_counter1 == 0) ctx->block_counter2++;
  }
}

/* given state h, do h <- P(h)+h */
void OutputTransformation(hashState *ctx) {
  int j;
  u32 *temp, *y, *z;
  temp = malloc(2*ctx->columns*sizeof(u32));
  y    = malloc(2*ctx->columns*sizeof(u32));
  z    = malloc(2*ctx->columns*sizeof(u32));

  /* determine variant */
  switch (ctx->v) {
  case SHORT :
    RND512(ctx->chaining,y,0,0);
    RND512(y,z,1,0);
    RND512(z,y,2,0);
    RND512(y,z,3,0);
    RND512(z,y,4,0);
    RND512(y,z,5,0);
    RND512(z,y,6,0);
    RND512(y,z,7,0);
    RND512(z,y,8,0);
    RND512(y,temp,9,0);
    for (j = 0; j < 2*COLS512; j++) {
      ctx->chaining[j] ^= temp[j];
    }
    break;
  case LONG  :
    RND1024(ctx->chaining,y,0,0);
    for (j = 1; j < ROUNDS1024-1; j += 2) {
      RND1024(y,z,j,0);
      RND1024(z,y,j+1,0);
    }
    RND1024(y,temp,ROUNDS1024-1,0);
    for (j = 0; j < 2*COLS1024; j++) {
      ctx->chaining[j] ^= temp[j];
    }
    break;
  }

  free(temp);
  free(y);
  free(z);
}

/* initialise context */
HashReturn Init(hashState* ctx,
		int hashbitlen) {
  /* output size (in bits) must be a positive integer less than or
     equal to 512, and divisible by 8 */
  if (hashbitlen <= 0 || (hashbitlen%8) || hashbitlen > 512)
    return BAD_HASHLEN;

  /* set number of state columns and state size depending on
     variant */
  if (hashbitlen <= 256) {
    ctx->columns = COLS512;
    ctx->statesize = SIZE512;
    ctx->v = SHORT;
  }
  else {
    ctx->columns = COLS1024;
    ctx->statesize = SIZE1024;
    ctx->v = LONG;
  }

  /* allocate memory for state and data buffer */
  ctx->chaining = calloc(ctx->statesize,1);
  ctx->buffer = malloc(ctx->statesize);
  if (ctx->chaining == NULL || ctx->buffer == NULL)
    return FAIL;

  /* set initial value */
  ctx->chaining[2*ctx->columns-1] = U32BIG((u32)hashbitlen);

  /* set other variables */
  ctx->hashbitlen = hashbitlen;
  ctx->buf_ptr = 0;
  ctx->block_counter1 = 0;
  ctx->block_counter2 = 0;
  ctx->bits_in_last_byte = 0;

  return SUCCESS;
}

/* update state with databitlen bits of input */
HashReturn Update(hashState* ctx,
		  const BitSequence* input,
		  DataLength databitlen) {
  int index = 0;
  int msglen = (int)(databitlen/8);
  int rem = (int)(databitlen%8);

  /* non-integral number of message bytes can only be supplied in the
     last call to this function */
  if (ctx->bits_in_last_byte) return FAIL;

  /* if the buffer contains data that has not yet been digested, first
     add data to buffer until full */
  if (ctx->buf_ptr) {
    while (ctx->buf_ptr < ctx->statesize && index < msglen) {
      ctx->buffer[(int)ctx->buf_ptr++] = input[index++];
    }
    if (ctx->buf_ptr < ctx->statesize) {
      /* buffer still not full, return */
      if (rem) {
	ctx->bits_in_last_byte = rem;
	ctx->buffer[(int)ctx->buf_ptr++] = input[index];
      }
      return SUCCESS;
    }

    /* digest buffer */
    ctx->buf_ptr = 0;
    Transform(ctx, ctx->buffer, ctx->statesize);
  }

  /* digest bulk of message */
  Transform(ctx, input+index, msglen-index);
  index += ((msglen-index)/ctx->statesize)*ctx->statesize;

  /* store remaining data in buffer */
  while (index < msglen) {
    ctx->buffer[(int)ctx->buf_ptr++] = input[index++];
  }

  /* if non-integral number of bytes have been supplied, store
     remaining bits in last byte, together with information about
     number of bits */
  if (rem) {
    ctx->bits_in_last_byte = rem;
    ctx->buffer[(int)ctx->buf_ptr++] = input[index];
  }
  return SUCCESS;
}

#define BILB ctx->bits_in_last_byte

/* finalise: process remaining data (including padding), perform
   output transformation, and write hash result to 'output' */
HashReturn Final(hashState* ctx,
		 BitSequence* output) {
  int i, j = 0, hashbytelen = ctx->hashbitlen/8;
  u8 *s = (BitSequence*)ctx->chaining;

  /* pad with '1'-bit and first few '0'-bits */
  if (BILB) {
    ctx->buffer[(int)ctx->buf_ptr-1] &= ((1<<BILB)-1)<<(8-BILB);
    ctx->buffer[(int)ctx->buf_ptr-1] ^= 0x1<<(7-BILB);
    BILB = 0;
  }
  else ctx->buffer[(int)ctx->buf_ptr++] = 0x80;

  /* pad with '0'-bits */
  if (ctx->buf_ptr > ctx->statesize-LENGTHFIELDLEN) {
    /* padding requires two blocks */
    while (ctx->buf_ptr < ctx->statesize) {
      ctx->buffer[(int)ctx->buf_ptr++] = 0;
    }
    /* digest first padding block */
    Transform(ctx, ctx->buffer, ctx->statesize);
    ctx->buf_ptr = 0;
  }
  while (ctx->buf_ptr < ctx->statesize-LENGTHFIELDLEN) {
    ctx->buffer[(int)ctx->buf_ptr++] = 0;
  }

  /* length padding */
  ctx->block_counter1++;
  if (ctx->block_counter1 == 0) ctx->block_counter2++;
  ctx->buf_ptr = ctx->statesize;

  while (ctx->buf_ptr > ctx->statesize-(int)sizeof(u32)) {
    ctx->buffer[(int)--ctx->buf_ptr] = (u8)ctx->block_counter1;
    ctx->block_counter1 >>= 8;
  }
  while (ctx->buf_ptr > ctx->statesize-LENGTHFIELDLEN) {
    ctx->buffer[(int)--ctx->buf_ptr] = (u8)ctx->block_counter2;
    ctx->block_counter2 >>= 8;
  }

  /* digest final padding block */
  Transform(ctx, ctx->buffer, ctx->statesize);
  /* perform output transformation */
  OutputTransformation(ctx);

  /* store hash result in output */
  for (i = ctx->statesize-hashbytelen; i < ctx->statesize; i++,j++) {
    output[j] = s[i];
  }

  /* zeroise relevant variables and deallocate memory */
  for (i = 0; i < ctx->columns; i++) {
    ctx->chaining[i] = 0;
  }
  for (i = 0; i < ctx->statesize; i++) {
    ctx->buffer[i] = 0;
  }
  free(ctx->chaining);
  free(ctx->buffer);

  return SUCCESS;
}

/* hash bit sequence */
HashReturn Hash(int hashbitlen,
		const BitSequence* data, 
		DataLength databitlen,
		BitSequence* hashval) {
  HashReturn ret;
  hashState context;

  /* initialise */
  if ((ret = Init(&context, hashbitlen)) != SUCCESS)
    return ret;

  /* process message */
  if ((ret = Update(&context, data, databitlen)) != SUCCESS)
    return ret;

  /* finalise */
  ret = Final(&context, hashval);

  return ret;
}

void PrintHash(const BitSequence* hash,
	       int hashbitlen) {
  int i;
  for (i = 0; i < hashbitlen/8; i++) {
    printf("%02x", hash[i]);
  }
  printf("\n");
}
