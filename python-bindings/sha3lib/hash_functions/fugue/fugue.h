#ifndef _FUGUE_H
#define _FUGUE_H

#include "fugue_t.h"

uint32 Init_Fugue (hashState *state, int hashbitlen);
uint32 Load_Fugue (hashState *state, int hashbitlen, const uint32 *iv_key, int ivwordlen);
uint32 Next_Fugue (hashState *state, const uint32 *data, uint64 datawordlen);
uint32 Done_Fugue (hashState *state, uint32 *hashval, int *hashwordlen);

#endif
