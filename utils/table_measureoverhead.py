VECTORS = ['1b','1kb','1mb','100mb','1gb']
OPS = ('p','g')

sha256_o = {
        '1bp':50.26,
        '1bg':49.63,
        '1kbp':81.83,
        '1kbg':86.41,
        '1mbp':67.71,
        '1mbg':61.73,
        '100mbp':137.90,
        '100mbg':120.79,
        '1gbp':273.66,
        '1gbg':239.45,
}

sha256_c = {
        '1bp':41.29,
        '1bg':39.28,
        '1kbp':58.19,
        '1kbg':56.92,
        '1mbp':45.98,
        '1mbg':40.68,
        '100mbp':101.43,
        '100mbg':99.75,
        '1gbp':213.45,
        '1gbg':194.03,
}

def calculate_overhead():
    results = {}
    for op in OPS:
        for tv in VECTORS:
            high = sha256_o[tv+op]
            low = sha256_c[tv+op]
            overhead = high - low
            k = [high, low, overhead]
            results[tv+op] = k
    return results

def print_results(results):
        for tv in VECTORS:
            for op in OPS:
                word = 'upload'
                if op=='g':
                    word = 'download'
                print "%s & %s & %ss & %ss & %ss \\\ \hline" % (tv.upper(),
                    word,
                    results[tv+op][0],
                    results[tv+op][1],
                    results[tv+op][2])

if __name__ == '__main__':
    k = calculate_overhead()
    print_results(k)
