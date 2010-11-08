from sha3lib import blake256
import random

def randByte():
    return random.randrange(0,255)

def randTup():
    return (chr(randByte()),
            chr(randByte()),
            chr(randByte()))


for i in xrange(0,5000000):
    k = blake256()
    r = randTup()
    k.update(r[0])
    k.update(r[1])
    k.update(r[2])
    blake256(k.digest()).digest()
    if i % 10000 == 0:
        print i
