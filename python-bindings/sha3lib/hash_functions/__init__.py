from bmw.bmw_hash import bmw
from groestl.groestl_hash import groestl
from echo.echo_hash import echo
from blake.blake import blake
from skein.skein_hash import skein
from luffa.luffa import luffa
from shavite3.shavite3 import shavite3
from simd.simd import simd
from keccak.keccak import keccak
from jh.jh_hash import jh
from fugue.fugue_hash import fugue
from shabal.shabal_hash import shabal
from cubehash.cubehash_hash import cubehash
from hamsi.hamsi_hash import hamsi

from bmw.bmw_hash import hash as bmw256hash
from groestl.groestl_hash import hash as groestl256hash
from echo.echo_hash import hash as echo256hash
from blake.blake import hash as blake256hash
from skein.skein_hash import hash as skein256hash
from luffa.luffa import hash as luffa256hash
from shavite3.shavite3 import hash as shavite3256hash
from simd.simd import hash as simd256hash
from keccak.keccak import hash as keccak256hash
from jh.jh_hash import hash as jh256hash
from fugue.fugue_hash import hash as fugue256hash
from shabal.shabal_hash import hash as shabal256hash
from cubehash.cubehash_hash import hash as cubehash256hash
from hamsi.hamsi_hash import hash as hamsi256hash

# skein ignored due to possible wrong kat-files or implementation
HASHES = ('blake', 'bmw', 'cubehash', 'echo', 'fugue', 'groestl', 'hamsi', 
            'jh', 'keccak', 'luffa', 'shabal', 'shavite3', 'simd', 'skein')
