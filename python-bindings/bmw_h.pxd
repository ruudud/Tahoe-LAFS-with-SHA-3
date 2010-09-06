cdef extern from "BlueMidnightWish.h":
    ctypedef unsigned char BitSequence
    ctypedef unsigned long long DataLength

    cdef enum HashReturn:
        SUCCESS = 0
        FAIL = 1
        BAD_HASHLEN = 2
        BAD_CONSECUTIVE_CALL_TO_UPDATE = 3 

    HashReturn Hash(int, BitSequence *data, DataLength, BitSequence *hashval)
