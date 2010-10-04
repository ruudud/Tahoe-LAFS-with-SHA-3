# coding: utf-8
from hash_functions import bmw,groestl,echo

HASHES = ('bmw256', 'echo256', 'groestl256',)

class bmw256(bmw):
    def __init__(self, initial=None):
        super(bmw256, self).__init__(256, initial)

class groestl256(groestl):
    def __init__(self, initial=None):
        super(groestl256, self).__init__(256, initial)

class echo256(echo):
    def __init__(self, initial=None):
        super(echo256, self).__init__(256, initial)
