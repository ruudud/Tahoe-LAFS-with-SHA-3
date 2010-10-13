#ifndef _SHA3API_REF_H
#define _SHA3API_REF_H

#include "fugue_t.h"

typedef uint8  BitSequence;
typedef uint64 DataLength;
typedef enum   { SUCCESS = 0, FAIL = 1, BAD_HASHBITLEN = 2 } HashReturn;

HashReturn Init (hashState *state, int hashbitlen);
HashReturn Update (hashState *state, const BitSequence *data, DataLength databitlen);
HashReturn Final (hashState *state, BitSequence *hashval);
HashReturn Hash (int hashbitlen, const BitSequence *data, DataLength databitlen, BitSequence *hashval);

#endif
