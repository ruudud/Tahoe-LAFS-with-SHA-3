cdef extern from "blake_opt32.h":
    ctypedef unsigned char BitSequence
    ctypedef unsigned long long DataLength
    
    cdef enum HashReturn:
        SUCCESS = 0
        FAIL = 1
        BAD_HASHBITLEN = 2

    ctypedef struct hashState:
        pass
 
    HashReturn Init(hashState *state, int hashbitlen)
    HashReturn Update(hashState *state, BitSequence *data, DataLength databitlen)
    HashReturn Final(hashState *state, BitSequence *hashval)
    HashReturn Hash(int hashbitlen, BitSequence *data, DataLength databitlen, BitSequence *hashval)
