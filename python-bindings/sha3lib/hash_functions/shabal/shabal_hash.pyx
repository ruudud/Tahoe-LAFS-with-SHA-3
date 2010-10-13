# encoding: utf-8
cimport shabal_hash_h
cimport cython

from libc.stdlib cimport *

def hash(int hashbitlen, bytes data, int in_length):
    '''
    Used for testing purposes.
    '''
    cdef char* c_string = <char *> data
    #cdef shabal_hash_h.DataLength datalen = in_length
    cdef size_t datalen = in_length
    #cdef shabal_hash_h.BitSequence *hashval = <shabal_h.BitSequence *> malloc(hashbitlen*8)
    cdef unsigned char *hashval = <unsigned char *> malloc(256*8)
    
    cdef shabal_hash_h.sph_shabal256_context mc

    shabal_hash_h.sph_shabal256_init(&mc)
    shabal_hash_h.sph_shabal256(&mc, data, datalen)
    shabal_hash_h.sph_shabal256_close(&mc,hashval)

    #shabal_hash_h.Hash(hashbitlen, <shabal_h.BitSequence *> c_string, datalen, hashval)

    try:
        digest = [hashval[i] for i from 0 <= i < hashbitlen / 8]
        digest = ''.join(['%02X' % i for i in digest])
    finally:
        free(hashval)

    return digest

cdef class shabal:
    '''
    A class that tries to mimic the behaviour of hashlib, i.e. keeping state
    so that one can update the hashing procedure instead of doing it from
    scratch.
    '''
    #cdef shabal_hash_h.BitSequence *hashval
    cdef unsigned char *hashval
    #cdef shabal_hash_h.hashState previous_state
    cdef shabal_hash_h.sph_shabal256_context previous_state
    #cdef shabal_hash_h.hashState state
    cdef shabal_hash_h.sph_shabal256_context state
    cdef int finished
    cdef size_t hashbitlen

    def __init__(self, int in_hashbitlen, bytes initial=None):
        self.finished = 0
        self.hashbitlen = 256 # Isn't really a choice
        shabal_hash_h.sph_shabal256_init(&self.state)

        if initial:
            self.update(initial)

    cpdef update(self, bytes in_data):
        cdef char* data = <char *> in_data
        cdef int data_len = len(in_data)*8

        if self.finished:
            self.finished = 0
            self.state = self.previous_state

        shabal_hash_h.sph_shabal256(&self.state, <unsigned char *> data, data_len)

    cpdef final(self):
        self.hashval = <unsigned char *> malloc(self.hashbitlen*8)

        # We copy the state so that we can continue to update.
        # This equals hashlibs functionality, but not pycryptopp.
        self.previous_state = self.state

        shabal_hash_h.sph_shabal256_close(&self.state, self.hashval)
        self.finished = 1

    cpdef copy(self):
        s = shabal(self.hashbitlen)
        s.state = self.state
        s.previous_state = self.previous_state
        s.finished = self.finished

        return s

    def digest(self):
        if not self.finished:
            self.final()

        digest = [self.hashval[i] for i from 0 <= i < self.hashbitlen / 8]
        return ''.join(map(chr, digest))

    def hexdigest(self):
        if not self.finished:
            self.final()

        digest = [self.hashval[i] for i from 0 <= i < self.hashbitlen / 8]

        # Return a hex string using str format specification
        return ''.join(['%02x' % i for i in digest])
