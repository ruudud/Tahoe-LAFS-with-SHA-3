cdef extern from "BlueMidnightWish.h":
    ctypedef unsigned char BitSequence
    ctypedef unsigned long long DataLength

    cdef enum HashReturn:
        SUCCESS = 0
        FAIL = 1
        BAD_HASHLEN = 2
        BAD_CONSECUTIVE_CALL_TO_UPDATE = 3 

    ctypedef struct Data256:
        pass

    ctypedef struct Data512:
        pass 

    ctypedef struct hashState:
        pass

    HashReturn Hash(int, BitSequence *data, DataLength, BitSequence *hashval)
    HashReturn Init(hashState *state, int)
    HashReturn Update(hashState *state, BitSequence *data, DataLength)
    HashReturn Final(hashState *state, BitSequence *hashval)
