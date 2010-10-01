cdef extern from "Groestl-opt.h":
    ctypedef unsigned char BitSequence
    ctypedef unsigned long long DataLength
    
    cdef enum Var:
        LONG
        SHORT

    cdef enum HashReturn:
        SUCCESS = 0
        FAIL = 1
        BAD_HASHLEN = 2

    ctypedef struct hashState:
        pass

    HashReturn Hash(int, BitSequence*, DataLength, BitSequence*)
    HashReturn Init(hashState*, int)
    HashReturn Update(hashState*, BitSequence*, DataLength)
    HashReturn Final(hashState*, BitSequence *)

