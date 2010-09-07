# encoding: utf-8
cimport bmw_h
cimport cython

from libc.stdlib cimport *

def hash(int hashbitlen, unsigned char[] data):
    cdef bmw_h.DataLength datalen = len(data) * 8
    cdef bmw_h.BitSequence *hashval = <bmw_h.BitSequence *> malloc(hashbitlen*8)
    
    bmw_h.Hash(hashbitlen, <bmw_h.BitSequence *> data, datalen, hashval)
    
    try:
        ret = [hashval[i] for i from 0 <= i < hashbitlen / 8]
    finally:
        free(hashval)

    return ret
