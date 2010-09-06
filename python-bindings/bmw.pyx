cimport bmw_h
cimport cython

from libc.stdlib cimport *

def hash(int hashbitlen, unsigned char[] data):
    cdef bmw_h.DataLength datalen = len(data)
    cdef bmw_h.BitSequence *hashval = <bmw_h.BitSequence *> malloc(hashbitlen*8)
    
    bmw_h.Hash(hashbitlen, <bmw_h.BitSequence *> data, datalen, hashval)
    
    try:
        ret = [hashval[i] for i from 0 <= i < hashbitlen]
    finally:
        free(hashval)
    return ret

#py_byte_string = py_unicode_string.encode('UTF-8')
#cdef char* c_string = py_byte_string
