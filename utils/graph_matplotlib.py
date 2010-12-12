import numpy as np
import os

import matplotlib.pyplot as plt

def graph_test_vector(candidates, data, directory, title, axis):
    if len(candidates) != len(data):
        raise AttributeError('Length of candidates and data does not match')
    print 'Plotting %s' % title
    ind = np.arange(len(candidates))
    width = 0.8

    plt.subplot(111)
    plt.title(title)

    plt.ylabel('Candidate')
    plt.yticks(ind + width*1.5, candidates)

    plt.xlabel(axis)
    plt.barh(ind+width, data, height=width, color='#3355cc')

    # Some tweaking to make it look alright.
    ymin, ymax = plt.ylim()
    plt.ylim((0, ymax + 0.5))
    plt.subplots_adjust(left=0.15)

    # Add value as a label right of graph
    for i in ind:
        plt.text(plt.xlim()[1]*1.01, ind[i] + width*1.25, '%.2f' % data[i])

    filename = '%s.svg' % title.replace(' ','')
    filepath = os.path.join(directory, filename)
    plt.savefig(filepath)

    #Clear the graphs, as it holds state
    plt.cla()
    plt.clf()
