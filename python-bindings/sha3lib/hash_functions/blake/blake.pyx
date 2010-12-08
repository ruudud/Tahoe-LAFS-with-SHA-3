# encoding: utf-8
cimport blake_h
cimport cython

from libc.stdlib cimport *

def hash(int hashbitlen, bytes data, int in_length):
    '''
    Used for testing purposes.
    '''
    cdef blake_h.state S
    cdef char* c_string = <char *> data
    cdef int data_len = in_length
    cdef blake_h.u8 *hashval = <blake_h.u8 *> malloc(hashbitlen*8)

    #blake_h.crypto_hash(hashval, c_string, datalen)
    blake_h.blake32_init(&S)
    blake_h.blake32_update(&S, <blake_h.u8 *> c_string, <blake_h.u64> in_length)
    blake_h.blake32_final(&S, hashval)

    try:
        digest = [hashval[i] for i from 0 <= i < hashbitlen / 8]
        digest = ''.join(['%02X' % i for i in digest])
    finally:
        free(hashval)

    return digest

cdef class blake:
    '''
    A class that tries to mimic the behaviour of hashlib, i.e. keeping state
    so that one can update the hashing procedure instead of doing it from
    scratch.
    '''
    #cdef blake_h.BitSequence *hashval
    #cdef blake_h.hashState previous_state
    cdef blake_h.state previous_state
    #cdef blake_h.hashState state
    cdef blake_h.state state
    cdef int finished
    cdef int hashbitlen
    cdef list hashval

    def __init__(self, int in_hashbitlen, bytes initial=None):
        self.finished = 0
        self.hashbitlen = in_hashbitlen
        #blake_h.Init(&self.state, self.hashbitlen)
        blake_h.blake32_init( &self.state)
        if initial:
            self.update(initial)

    cpdef update(self, bytes in_data):
        cdef char* data = <char *> in_data
        cdef unsigned long long data_len = len(in_data)
        data_len *= 8

        if self.finished:
            self.finished = 0
            self.state = self.previous_state

        #blake_h.Update(&self.state, <blake_h.BitSequence *> data, data_len)
        blake_h.blake32_update(&self.state, <blake_h.u8 *> data, <blake_h.u64> data_len)

    cpdef final(self):
        #cdef blake_h.BitSequence *hashval = <blake_h.BitSequence *> malloc(self.hashbitlen*8)
        cdef blake_h.u8 *hashval = <blake_h.u8 *> malloc(self.hashbitlen*8)

        # We copy the state so that we can continue to update.
        # This equals hashlibs functionality, but not pycryptopp.
        self.previous_state = self.state

        #blake_h.Final(&self.state, hashval)
        blake_h.blake32_final(&self.state, hashval)
        self.finished = 1
        
        self.hashval = [hashval[i] for i from 0 <= i < self.hashbitlen / 8]
        free(hashval)

    cpdef copy(self):
        s = blake(self.hashbitlen)
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

        #digest = [self.hashval[i] for i from 0 <= i < self.hashbitlen / 8]

        # Return a hex string using str format specification
        return ''.join(['%02x' % i for i in self.hashval])
