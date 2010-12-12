#!/usr/bin/python
"""
A tool to download graphs based on results from the measurements in the
SHA-3 in Tahoe-LAFS project, using Google Chart API.

Requirements:
Modified pygooglechart with ScaledTextData data class.

Missing features:
o Some sort of cache, maybe in the form of a json/pickling file.

"""
import getopt
import os
import sys
#from graph_googlechart import graph_test_vector
from graph_matplotlib import graph_test_vector

VECTORS = ('1b', '1kb', '1mb', '100mb', '1gb')
VECTOR_COUNT = {'1b': 1000, '1kb': 100, '1mb': 50, '100mb': 5, '1gb': 1}
OPERATIONS = {'get': ('tshg', 'totaltimeget', 'nohashopsg'),
              'put': ('tshp', 'totaltimeput', 'nohashopsp'),}

def get_candidates(directory=None):
    sub_directories = [f for f in os.listdir(directory) if os.path.isdir(
        os.path.join(directory, f))]
    sub_directories.sort()
    return sub_directories

def read_results(directory, candidate, vector):
    base_path = os.path.join(directory, candidate)

    results = {'put': None, 'get': None}
    for cmd, items in OPERATIONS.items():
        cmd_results = []
        for op in items:
            file_path = os.path.join(base_path, '%s_%s.txt' % (vector, op))
            fp = open(file_path, 'r')
            value = float(fp.readline())
            fp.close()
            cmd_results.append(value)

        results[cmd] = tuple(cmd_results)

    return results

def get_results_from_data(candidates, directory):
    """
    Return value example:
    {
        '100mb': {
                'candidate': {
                        'get': ('time_spent_hashing', 'total_time',
                                'number_of_hashops'),
                        'put': ('time_spent_hashing', 'total_time',
                                'number_of_hashops'),
                    },
                'BMW': {
                        'get': (88.3, 9888.3, 2999.0),
                        'put': (983488.3, 2929239838.3, 19834999.0),
            },
        '1gb': {
                'candidate': {
                        'get': ('time_spent_hashing', 'total_time',
                                'number_of_hashops'),
                        'put': ('time_spent_hashing', 'total_time',
                                'number_of_hashops'),
                    },
            }
    }
    """
    results = {}
    for v in VECTORS:
        results[v] = {}
        for c in candidates:
            v_numbers = read_results(directory, c, v)
            results[v][c] = {'get': v_numbers['get'], 'put': v_numbers['put']}

    return results

def graph_data(results, candidates, directory):
    for vector in VECTORS:
        for op in ('get', 'put'):
            if op == 'get':
                op_txt = 'downloading'
            else:
                op_txt = 'uploading'
            plural = ''
            if VECTOR_COUNT[vector] > 1:
                plural = 's'
            y_axis = 'Seconds'

            tsh_data = [results[vector][c][op][0] for c in candidates]
            title = 'Time spent hashing while %s %s %s file%s' % (
                op_txt, str(VECTOR_COUNT[vector]), vector.upper(), plural)
            graph_test_vector(candidates, tsh_data, directory, title, y_axis)

            tts_data = [results[vector][c][op][1] for c in candidates]
            title = 'Total time spent while %s %s %s file%s' % (
                op_txt, str(VECTOR_COUNT[vector]), vector.upper(), plural)
            graph_test_vector(candidates, tts_data, directory, title, y_axis)

            data = map(lambda x, y: float(y) - float(x), tsh_data, tts_data)
            title = 'Time spent NOT hashing while %s %s %s file%s' % (
                op_txt, str(VECTOR_COUNT[vector]), vector.upper(), plural)
            graph_test_vector(candidates, data, directory, title, y_axis)

            y_axis = 'Count'
            data = [results[vector][c][op][2] for c in candidates]
            title = 'Hash operations %s %s %s file%s' % (
                op_txt, str(VECTOR_COUNT[vector]), vector.upper(), plural)
            graph_test_vector(candidates, data, directory, title, y_axis)

def results_to_graphs(directory=None):
    if directory is None:
        directory = os.getcwd()
    candidates = get_candidates(directory)
    results = get_results_from_data(candidates, directory)
    graph_data(results, candidates, directory)

def usage():
    usage = """Export results to graphs.
    -d <dir>
    --directory=<dir>
      Generate graphs for candidates in <dir>

    -h
    --help
      Output this help.
    """
    print usage

def main(argv=None):
    if argv is None:
        argv = sys.argv

    try:
        opts, args = getopt.getopt(argv[1:], 'hd:', ['help', 'directory='])
        if len(opts) == 0 and len(args) != 0:
            raise getopt.GetoptError('Invalid argument')
    except getopt.GetoptError as err:
        print(err)
        usage()
        return 2

    directory = None
    for o, a in opts:
        if o in ('-h', '--help'):
            usage()
            return 0
        elif o in ('-d', '--directory'):
            directory = a
        else:
            assert False, 'Unhandled option'

    results_to_graphs(directory)
    return 0

if __name__ == "__main__":
    sys.exit(main())
