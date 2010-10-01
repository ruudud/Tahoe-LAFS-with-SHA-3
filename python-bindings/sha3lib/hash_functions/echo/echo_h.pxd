cdef extern from "echo32.h":
    ctypedef unsigned char BitSequence
    ctypedef unsigned long long DataLength
    
    cdef enum Var:
        LONG
        SHORT

    cdef enum HashReturn:
        SUCCESS = 0
        FAIL = 1
        BAD_HASHBITLEN = 2
        UPDATE_WBITS_TWICE = 4

    ctypedef struct hashState:
        pass

    
    HashReturn Init(hashState *state, unsigned int hashbitlen)
    HashReturn Compress(hashState *state)
    HashReturn Update(hashState *state, BitSequence *data, DataLength databitlen)
    HashReturn Final(hashState *state, BitSequence *hashval)
    HashReturn Hash(int hashbitlen, BitSequence *data, DataLength databitlen, BitSequence *hashval)
