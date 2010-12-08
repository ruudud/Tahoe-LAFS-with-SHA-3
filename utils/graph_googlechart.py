import os

from pygooglechart import StackedVerticalBarChart

def graph_test_vector(candidates, data, directory, title, y_axis):
    if len(candidates) != len(data):
        raise AttributeError('Length of candidates and data does not match')

    chart = StackedVerticalBarChart(700, 428, auto_scale=False,
                                    custom_scaling=True)
    chart.set_bar_width(41)
    chart.set_colours(('3366CC', '000000'))
    chart.add_data(data)
    chart.set_axis_range('y', 0, max(data) + 0.1 * max(data))
    chart.set_axis_labels('x', candidates)
    x_title_index = chart.set_axis_labels('x', ['Candidate'])
    y_title_index = chart.set_axis_labels('y', [y_axis])
    chart.set_axis_positions(x_title_index, [50])
    chart.set_axis_positions(y_title_index, [50])
    chart.set_title(title)

    # (dataset, all bars, formating, colour, width)
    chart.add_marker(0, -1, 'N', '000000', 11)
    chart.download(os.path.join(directory, '%s.png' % title.replace(' ','')))
