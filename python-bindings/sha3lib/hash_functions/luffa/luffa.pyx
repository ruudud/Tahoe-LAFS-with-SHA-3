# encoding: utf-8
cimport luffa_h
cimport cython

from libc.stdlib cimport *

def hash(int hashbitlen, bytes data, int in_length):
    '''
    Used for testing purposes.
    '''
    cdef char* c_string = <char *> data
    cdef luffa_h.DataLength datalen = in_length
    cdef luffa_h.BitSequence *hashval = <luffa_h.BitSequence *> malloc(hashbitlen*8)

    luffa_h.Hash(hashbitlen, <luffa_h.BitSequence *> c_string, datalen, hashval)

    try:
        digest = [hashval[i] for i from 0 <= i < hashbitlen / 8]
        digest = ''.join(['%02X' % i for i in digest])
    finally:
        free(hashval)

    return digest

cdef class luffa:
    '''
    A class that tries to mimic the behaviour of hashlib, i.e. keeping state
    so that one can update the hashing procedure instead of doing it from
    scratch.
    '''
    #cdef luffa_h.BitSequence *hashval
    cdef luffa_h.hashState previous_state
    cdef luffa_h.hashState state
    cdef int finished
    cdef int hashbitlen
    cdef list hashval

    def __init__(self, int in_hashbitlen, bytes initial=None):
        self.finished = 0
        self.hashbitlen = in_hashbitlen
        
        cdef luffa_h.hashState state
        luffa_h.Init(&state, self.hashbitlen)
        self.state = state

        if initial:
            self.update(initial)

    cpdef update(self, bytes in_data):
        cdef char* data = <char *> in_data
        cdef unsigned long long data_len = len(in_data)
        data_len *= 8

        if self.finished:
            self.finished = 0
            self.state = self.previous_state
        
        cdef luffa_h.hashState state = self.state
        luffa_h.Update(&state, <luffa_h.BitSequence *> data, data_len)
        self.state = state

    cpdef final(self):
        cdef luffa_h.BitSequence *hashval = <luffa_h.BitSequence *> malloc(self.hashbitlen*8)

        # We copy the state so that we can continue to update.
        # This equals hashlibs functionality, but not pycryptopp.
        self.previous_state = self.state
        
        cdef luffa_h.hashState state = self.state
        luffa_h.Final(&state, hashval)
        self.state = state
        self.finished = 1
        
        self.hashval = [hashval[i] for i from 0 <= i < self.hashbitlen / 8]
        free(hashval)

    cpdef copy(self):
        s = luffa(self.hashbitlen)
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
