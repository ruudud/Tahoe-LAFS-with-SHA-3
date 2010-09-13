# encoding: utf-8
cimport bmw_h
cimport cython

from libc.stdlib cimport *

def hash(int hashbitlen, unsigned char[] data):
    '''
    We keep this for now, for debugging purposes.
    '''
    cdef bmw_h.DataLength datalen = len(data) * 8
    cdef bmw_h.BitSequence *hashval = <bmw_h.BitSequence *> malloc(hashbitlen*8)

    bmw_h.Hash(hashbitlen, <bmw_h.BitSequence *> data, datalen, hashval)

    try:
        ret = [hashval[i] for i from 0 <= i < hashbitlen / 8]
    finally:
        free(hashval)

    return ret

cdef class bmw256:
    '''
    A class that tries to mimic the behaviour of hashlib, i.e. keeping state
    so that one can update the hashing procedure instead of doing it from
    scratch.
    '''
    cdef bmw_h.hashState state
    cdef bmw_h.hashState previous_state
    cdef int hashbitlen
    cdef bmw_h.BitSequence *hashval
    cdef int finished

    def __init__(self, initial=None):
        self.finished = 0
        self.hashbitlen = 256
        bmw_h.Init(&self.state, self.hashbitlen)

        if initial:
            self.update(initial)

    cpdef update(self, unsigned char data[]):
        if self.finished:
            self.finished = 0
            self.state = self.previous_state

        bmw_h.Update(&self.state, data, len(data)*8)

    cpdef final(self):
        self.hashval = <bmw_h.BitSequence *> malloc(self.hashbitlen*8)
        self.previous_state = self.state

        bmw_h.Final(&self.state, self.hashval)
        self.finished = 1

    cpdef copy(self):
        s = bmw256()
        s.state = self.state
        s.previous_state = self.previous_state
        s.finished = self.finished

        return s

    def hexdigest(self):
        if not self.finished:
            self.final()

        ret = [self.hashval[i] for i from 0 <= i < self.hashbitlen / 8]

        # Return a hex string
        return ''.join(['%02x' % i for i in ret])
