cdef extern from "sph_shabal.h":

    ctypedef struct sph_shabal_context:
        pass

    ctypedef sph_shabal_context sph_shabal256_context

    void sph_shabal256_init(sph_shabal256_context *cx)
    void sph_shabal256(sph_shabal256_context *cx, unsigned char *data, size_t datalen)
    void sph_shabal256_close(sph_shabal256_context *cx, unsigned char *out)
