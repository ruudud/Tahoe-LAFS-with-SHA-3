cdef extern from "hash.h":
    ctypedef unsigned char u8
    ctypedef unsigned long long u64
    ctypedef unsigned int u32
    
    ctypedef struct state:
        pass
 
    #HashReturn Init(hashState *state, int hashbitlen)
    #HashReturn Update(hashState *state, BitSequence *data, DataLength databitlen)
    #HashReturn Final(hashState *state, BitSequence *hashval)
    #HashReturn Hash(int hashbitlen, BitSequence *data, DataLength databitlen, BitSequence *hashval)
    void blake32_init( state *S )
    void blake32_update( state *S, u8 *data, u64 datalen)
    void blake32_final( state *S, u8 *digest)
    int crypto_hash( unsigned char *out, unsigned char *data , unsigned long long inlen)
