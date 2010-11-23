#!/usr/bin/python
import getopt
import os
import sys
from pygooglechart import StackedVerticalBarChart

def get_candidates(directory=None):
    sub_directories = [os.path.join(directory, f) for f in os.listdir(directory)
        if os.path.isdir(os.path.join(directory, f))]
    return sub_directories

def get_results_from_data(candidates):
    """
    Return value example:
    {
        '100MB': {
                'candidate': {
                        'get': ('time_in_sec', 'number_of_hashops'),
                        'put': ('time_in_sec', 'number_of_hashops'),
                    },
                'BMW': {
                        'get': (88.3, 2999.0),
                        'put': (983488.3, 19834999.0),
            },
        '1GB': {
                'candidate': {
                        'get': ('time_in_sec', 'number_of_hashops'),
                        'put': ('time_in_sec', 'number_of_hashops'),
                    },
            }
    }
    """
    results = {}

    for cd in candidates:
        pass

def graph_test_vector(candidates, data, operation, count, vector):
    if len(candidates) != len(data):
        raise AttributeError('Length of candidates and data does not match')

    chart = StackedVerticalBarChart(400, 400)
    chart.set_bar_width(41)
    chart.set_colours(('3366CC', '000000'))
    chart.add_data(data)
    chart.set_axis_range('y', 0, 40)
    chart.set_axis_labels('x', candidates)
    x_title_index = chart.set_axis_labels('x', ['Candidate'])
    y_title_index = chart.set_axis_labels('y', ['Seconds'])
    chart.set_axis_positions(x_title_index, [50])
    chart.set_axis_positions(y_title_index, [50])

    chart.set_title('%s of %s %s file(s)' % (operation, str(count), vector))

    # (dataset, all bars, formating, colour, width)
    chart.add_marker(0, -1, 'N', '000000', 11)

    chart.download('%s%s.png' % (vector, op))

def graph_data(data):
    pass

def results_to_graphs(directory=None):
    if directory is None:
        directory = os.getcwd()
    candidates = get_candidates(directory)
    results = get_results_from_data(candidates)
    graph_data(results)
    print candidates

def usage():
    usage = """Export results to CSV file.
    -d <dir> 
    --directory=<dir> 
      Generate CSV for candidates in <dir>

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
