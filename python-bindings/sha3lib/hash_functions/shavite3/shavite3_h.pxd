cdef extern from "SHA3api_ref.h":
    ctypedef unsigned char BitSequence
    ctypedef unsigned long long DataLength
    
    cdef enum HashReturn:
        SUCCESS = 0
        FAIL = 1
        BAD_HASHBITLEN = 2

    ctypedef struct hashState:
        pass

    
    HashReturn Init(hashState *state, unsigned int hashbitlen)
    HashReturn Compress(hashState *state)
    HashReturn Update(hashState *state, BitSequence *data, DataLength databitlen)
    HashReturn Final(hashState *state, BitSequence *hashval)
    HashReturn Hash(int hashbitlen, BitSequence *data, DataLength databitlen, BitSequence *hashval)
