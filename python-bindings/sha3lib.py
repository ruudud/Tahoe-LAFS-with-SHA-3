# coding: utf-8

from bmw import bmw
from groestl import groestl

class bmw256(bmw):
    def __init__(self, initial=None):
        super(bmw256, self).__init__(256, initial)

class groestl256(groestl):
    def __init__(self, initial=None):
        super(groestl256, self).__init__(256, initial)
