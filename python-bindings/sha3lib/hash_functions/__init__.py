from bmw.bmw import bmw
from groestl.groestl import groestl
from echo.echo import echo
from blake.blake import blake
from skein.skein_hash import skein
from luffa.luffa import luffa

from bmw.bmw import hash as bmw256hash
from groestl.groestl import hash as groestl256hash
from echo.echo import hash as echo256hash
from blake.blake import hash as blake256hash
from skein.skein_hash import hash as skein256hash
from luffa.luffa import hash as luffa256hash

HASHES = ('bmw', 'echo', 'groestl', 'blake', 'luffa')
