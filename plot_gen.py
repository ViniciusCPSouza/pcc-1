#!/usr/bin/env python

"""
Script to generate plots with the results of string searching algorithms.

<input_folder> The folder where the results can be found.

Usage:
    plot_gen.py <input_folder>
"""

import csv
import os
import re

from docopt import docopt
import plotly.plotly as py
import plotly.graph_objs as go


DISPLAY_NAMES = {"brute_force": "Naive",
                 "kmp": "Knuth-Morris-Pratt",
                 "shift_or": "Shift Or",
                 "wu_mamber": "Wu-Manber",
                 "levenshtein": "Sellers (Levenshtein)",}


DATASET_REGEX = re.compile(r'A(?P<alphabet_size>[a-z]{2})P(?P<pattern_min>[0-9]+)_(?P<pattern_max>[0-9]+)_E(?P<edit_distance>[0-9])')


def parse_dataset_name(dataset):
    return ("Alfabeto '{alphabet_size}', Padrões de tamanho {pattern_min} a {pattern_max}, Distância de Edição {edit_distance}"
            .format(**DATASET_REGEX.match(dataset).groupdict()))


def main(args):
    input_folder = args['<input_folder>']

    for dataset in os.listdir(input_folder):
        dataset_path = os.path.join(input_folder, dataset)

        data = []
        layout = go.Layout(title=parse_dataset_name(dataset), width=800, height=640,
                           xaxis=dict(title='Tamanho do Padrão'),
                           yaxis=dict(title='Tempo de Execução (segundos)'))

        for algorithm in os.listdir(dataset_path):
            algorithm_path = os.path.join(dataset_path, algorithm)

            with open(os.path.join(algorithm_path, 'runtime.csv')) as csvfile:
                runtime = csv.DictReader(csvfile, delimiter=',')

                x = []
                y = []
                for row in runtime:
                    x.append(int(row["pattern_size"]))
                    y.append(int(row["runtime"]) / 1000000000)

                data.append(go.Scatter(x=x, y=y, mode = 'lines', name=DISPLAY_NAMES[algorithm]))

        figure = go.Figure(data=data, layout=layout)
        os.makedirs("plots", exist_ok=True)
        py.image.save_as(figure, filename='plots/%s.png' % dataset)


if __name__ == "__main__":
    main(docopt(__doc__))
