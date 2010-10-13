#ifndef _FUGUE_384_H
#define _FUGUE_384_H

#include "fugue_t.h"
#include "aestab_t.h"

int fugue_update_384 (hashState *hs, const char *in, uint_64t len);
int fugue_final_384  (hashState *hs, char *out);

#endif
