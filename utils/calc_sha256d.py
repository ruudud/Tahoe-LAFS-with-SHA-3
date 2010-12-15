sha256d = {
    'long':15.14,
    4096:15.83,
    1563:16.45,
    576:18.05,
    64:38.12,
    8:179.62,
}

def calc_sha256d(worst):
    d = 38.12
    if worst:
        d = 179.62
    if worst==2:
        d = interpol32()

    print "4096:\t"+  calc1(sha256d[4096],4096,d)
    print "1563:\t"+  calc1(sha256d[1563],1563,d)
    print "576:\t" +  calc1(sha256d[576],576,d)
    print "64:\t"  +  calc1(sha256d[64],64,d)
    print "8:\t"   +  calc1(sha256d[8],8,d)

def interpol32():
    k = 64 - 8
    r = 179.62 - 38.12
    f = float(r / k)
    s = 179.62 - 24*f
    return s


def calc1(orgcb, length, extra):
    k = orgcb * length + extra * 32
    r = float(k/length)
    return "%0.3f" % r


print "worst case"
calc_sha256d(True)

print "\nbest case"
calc_sha256d(False)

print "\ninterpol case"
calc_sha256d(2)

print interpol32()
