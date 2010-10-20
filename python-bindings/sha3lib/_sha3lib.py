# coding: utf-8
from hash_functions import(bmw,groestl,echo,blake,skein, 
        luffa,shavite3,simd,keccak,jh,fugue,shabal,cubehash,
        hamsi)

class bmw256(bmw):
    def __init__(self, initial=None):
        super(bmw256, self).__init__(256, initial)

class groestl256(groestl):
    def __init__(self, initial=None):
        super(groestl256, self).__init__(256, initial)

class echo256(echo):
    def __init__(self, initial=None):
        super(echo256, self).__init__(256, initial)

class blake256(blake):
    def __init__(self, initial=None):
        super(blake256, self).__init__(256, initial)

class skein256(skein):
    def __init__(self, initial=None):
        super(skein256, self).__init__(256, initial)

class luffa256(luffa):
    def __init__(self, initial=None):
        super(luffa256, self).__init__(256, initial)

class shavite3256(shavite3):
    def __init__(self, initial=None):
        super(shavite3256, self).__init__(256, initial)

class simd256(simd):
    def __init__(self, initial=None):
        super(simd256, self).__init__(256, initial)

class keccak256(keccak):
    def __init__(self, initial=None):
        super(keccak256, self).__init__(256, initial)

class jh256(jh):
    def __init__(self, initial=None):
        super(jh256, self).__init__(256, initial)

class fugue256(fugue):
    def __init__(self, initial=None):
        super(fugue256, self).__init__(256, initial)

class shabal256(shabal):
    def __init__(self, initial=None):
        super(shabal256, self).__init__(256, initial)

class cubehash256(cubehash):
    def __init__(self, initial=None):
        super(cubehash256, self).__init__(256, initial)

class hamsi256(hamsi):
    def __init__(self, initial=None):
        super(hamsi256, self).__init__(256, initial)
