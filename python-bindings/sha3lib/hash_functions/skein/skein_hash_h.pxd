cdef extern from "SHA3api_ref.h":
    ctypedef unsigned char BitSequence
    ctypedef size_t DataLength
    
    cdef enum HashReturn:
        SUCESS = 0
        FAIL = 1
        BASH_HASHLEN = 2

    ctypedef struct hashState:
        pass
 
    HashReturn Init(hashState *state, int hashbitlen)
    HashReturn Update(hashState *state, BitSequence *data, DataLength databitlen)
    HashReturn Final(hashState *state, BitSequence *hashval)
    HashReturn Hash(int hashbitlen, BitSequence *data, DataLength databitlen, BitSequence *hashval)
