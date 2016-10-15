#!/usr/bin/env python

"""
Script to place .

<alphabet_size> The size of the alphabet. Possible values are 'sm' and 'lg'.
<pattern_size> The size of the pattern. Possible values are 'sm' and 'lg'.
<text_line_size> The size of each line of text. Possible values are 'sm' and 'lg'.
<data_set_name> The name of the generated dataset.

Usage:
    pattern_gen.py <alphabet_size> <pattern_size> <text_line_size> <dataset_name>
"""

import os
import random
import shutil
import string

from docopt import docopt


SIZE_SM = "sm"
SIZE_LG = "lg"

ALPHABETS = {"sm": ["A", "C", "G", "T"],
             "lg": string.ascii_letters}

PATTERN_SIZES = {"sm": 5, "lg": 30}
PATTERN_COUNT = 100

TEXT_LINE_SIZES = {"sm": 250, "lg": 3000}
TEXT_FILES_COUNT = 5
TEXT_LINES_COUNT = 10000

OUTPUT_FOLDER = "datasets"


def main(args):
    a_size = args['<alphabet_size>']
    p_size = args['<pattern_size>']
    t_size = args['<text_line_size>']
    dataset_name = args['<dataset_name>']

    dataset_folder = os.path.join(OUTPUT_FOLDER, dataset_name)
    text_folder = os.path.join(dataset_folder, "txt")
    patterns_filepath = os.path.join(dataset_folder, "patterns.txt")

    if os.path.exists(dataset_folder):
        shutil.rmtree(dataset_folder)

    os.makedirs(dataset_folder)
    os.makedirs(text_folder)

    patterns = ["".join(random.choice(ALPHABETS[a_size]) for _ in range(PATTERN_SIZES[p_size]))
                for _ in range(PATTERN_COUNT)]

    # generate pattern
    with open(patterns_filepath, "w") as f:
        for p in patterns:
            f.write(p)
            f.write("\n")

    print(patterns)

    # generate texts
    for i in range(TEXT_FILES_COUNT):
        with open(os.path.join(text_folder, "text%d.txt" % i), "w") as f:
            for _ in range(TEXT_LINES_COUNT):
                f.write("".join(random.choice(ALPHABETS[a_size]) for _ in range(TEXT_LINE_SIZES[t_size])))
                f.write("\n")


if __name__ == "__main__":
    main(docopt(__doc__))
