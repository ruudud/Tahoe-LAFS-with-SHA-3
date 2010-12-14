VECTORS = ['1b','1kb','1mb','100mb','1gb']
OPS = ('p','g')

blake_o = {
        '1bp':0.374,
        '1bg':0.519,
        '1kbp':1.133,
        '1kbg':1.448,
        '1mbp':1.96,
        '1mbg':1.445,
        '100mbp':10.09,
        '100mbg':5.03,
        '1gbp':20.28,
        '1gbg':10.12,
}

blake_c = {
        '1bp':0.16,
        '1bg':0.15,
        '1kbp':0.39,
        '1kbg':0.40,
        '1mbp':1.30,
        '1mbg':0.72,
        '100mbp':9.33,
        '100mbg':4.56,
        '1gbp':19.21,
        '1gbg':9.27,
}

def calculate_overhead():
    results = {}
    for op in OPS:
        for tv in VECTORS:
            high = blake_o[tv+op]
            low = blake_c[tv+op]
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
                print "%s & %s & %s & %s & %s \\\ \hline" % (tv.upper(),
                    word,
                    results[tv+op][0],
                    results[tv+op][1],
                    results[tv+op][2])

if __name__ == '__main__':
    k = calculate_overhead()
    print_results(k)
