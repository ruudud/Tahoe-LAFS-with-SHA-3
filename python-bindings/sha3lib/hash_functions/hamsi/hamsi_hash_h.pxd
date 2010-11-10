cdef extern from "hamsi.h":
    ctypedef unsigned char BitSequence
    ctypedef unsigned long long DataLength

    cdef enum HashReturn:
        SUCCESS = 0
        FAIL = 1
        BAD_HASHBITLEN = 2

    ctypedef struct hashState:
        pass

    HashReturn Hash(int, BitSequence *data, DataLength, BitSequence *hashval)
    HashReturn Init(hashState* state, int hashbitlen)
    HashReturn Update(hashState *state, BitSequence *data, DataLength databitlen)
    HashReturn Final(hashState *state, BitSequence *hashval)
