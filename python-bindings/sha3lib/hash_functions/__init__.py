from bmw.bmw import bmw
from groestl.groestl import groestl
from echo.echo import echo
from blake.blake import blake
from skein.skein_hash import skein
from luffa.luffa import luffa
from shavite3.shavite3 import shavite3
from simd.simd import simd
from keccak.keccak import keccak
from jh.jh import jh

from bmw.bmw import hash as bmw256hash
from groestl.groestl import hash as groestl256hash
from echo.echo import hash as echo256hash
from blake.blake import hash as blake256hash
from skein.skein_hash import hash as skein256hash
from luffa.luffa import hash as luffa256hash
from shavite3.shavite3 import hash as shavite3256hash
from simd.simd import hash as simd256hash
from keccak.keccak import hash as keccak256hash
from jh.jh import hash as jh256hash

# skein ignored due to possible wrong kat-files or implementation
HASHES = ('bmw', 'echo', 'groestl', 'blake', 'luffa', 'shavite3', 'simd',
'keccak','jh')
