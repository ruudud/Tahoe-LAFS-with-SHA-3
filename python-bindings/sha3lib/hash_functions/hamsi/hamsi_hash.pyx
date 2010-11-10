# encoding: utf-8
cimport hamsi_hash_h
cimport cython

from libc.stdlib cimport *

def hash(int hashbitlen, bytes data, int in_length):
    '''
    Used for testing purposes.
    '''
    cdef char* c_string = <char *> data
    cdef hamsi_hash_h.DataLength datalen = in_length
    cdef hamsi_hash_h.BitSequence *hashval = <hamsi_hash_h.BitSequence *> malloc(hashbitlen*8)
    
    #cdef hamsi_hash_h.hashState state
    #hamsi_hash_h.Init(&state, 256)
    #return 0

    hamsi_hash_h.Hash(hashbitlen, <hamsi_hash_h.BitSequence *> c_string, datalen, hashval)

    try:
        digest = [hashval[i] for i from 0 <= i < hashbitlen / 8]
        digest = ''.join(['%02X' % i for i in digest])
    finally:
        free(hashval)

    return digest

cdef class hamsi:
    '''
    A class that tries to mimic the behaviour of hashlib, i.e. keeping state
    so that one can update the hashing procedure instead of doing it from
    scratch.
    '''
    #cdef hamsi_hash_h.BitSequence *hashval
    cdef hamsi_hash_h.hashState previous_state
    cdef hamsi_hash_h.hashState state
    cdef int finished
    cdef int hashbitlen
    cdef list hashval

    def __init__(self, int in_hashbitlen, bytes initial=None):
        self.finished = 0
        self.hashbitlen = in_hashbitlen
        cdef hamsi_hash_h.hashState state
        hamsi_hash_h.Init(&state, 256)
        self.state = state
        
        if initial:
            self.update(initial)

    cpdef update(self, bytes in_data):
        cdef char* data = <char *> in_data
        cdef int data_len = len(in_data)*8

        if self.finished:
            self.finished = 0
            self.state = self.previous_state

        self.c_update(data, data_len)

    cdef c_update(self, char* data, int data_len):
        cdef hamsi_hash_h.hashState state = self.state
        hamsi_hash_h.Update(&state, <hamsi_hash_h.BitSequence *> data, data_len)
        self.state = state

    cpdef final(self):
        cdef hamsi_hash_h.BitSequence *hashval = <hamsi_hash_h.BitSequence *> malloc(self.hashbitlen*8)

        # We copy the state so that we can continue to update.
        # This equals hashlibs functionality, but not pycryptopp.
        self.previous_state = self.state
        
        cdef hamsi_hash_h.hashState state = self.state
        hamsi_hash_h.Final(&state, hashval)
        self.finished = 1
        
        self.hashval = [hashval[i] for i from 0 <= i < self.hashbitlen / 8]
        self.state = state
        free(hashval)

    cpdef copy(self):
        s = hamsi(self.hashbitlen)
        s.state = self.state
        s.previous_state = self.previous_state
        s.finished = self.finished
        if s.finished:
            s.hashval = self.hashval

        return s

    def digest(self):
        if not self.finished:
            self.final()

        return ''.join(map(chr, self.hashval))

    def hexdigest(self):
        if not self.finished:
            self.final()

        return ''.join(['%02x' % i for i in self.hashval])
