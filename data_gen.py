#!/usr/bin/env python

"""
Script to place .

<alphabet_size> The size of the alphabet. Possible values are 'sm' and 'lg'.
<pattern_size> The size of the pattern. Possible values are 'sm' and 'lg'.
<text_line_size> The size of each line of text. Possible values are 'sm' and 'lg'.
<edit_distance> A number that indicates the edit distance that each match should have.
<data_set_name> The name of the generated dataset. If it is set to 'auto', the parameters will decide the name.

Usage:
    pattern_gen.py <alphabet_size> <pattern_size> <text_line_size> <edit_distance> <dataset_name>
"""

import math
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

TEXT_LINE_SIZES = {"sm": 1000, "lg": 5000}
TEXT_FILES_COUNT = 5
TEXT_LINES_COUNT = 10000

OUTPUT_FOLDER = "datasets"


def main(args):
    a_size = args['<alphabet_size>']
    p_size = args['<pattern_size>']
    t_size = args['<text_line_size>']
    edit_distance = int(args['<edit_distance>'])
    dataset_name = args['<dataset_name>']

    get_chars = lambda alphabet, n: (random.choice(alphabet) for _ in range(n))

    if dataset_name == "auto":
        dataset_name = "A%sP%sT%s_E%d" % (a_size, p_size, t_size, edit_distance)

    dataset_folder = os.path.join(OUTPUT_FOLDER, dataset_name)
    text_folder = os.path.join(dataset_folder, "txt")
    patterns_filepath = os.path.join(dataset_folder, "patterns.txt")

    if os.path.exists(dataset_folder):
        shutil.rmtree(dataset_folder)

    os.makedirs(dataset_folder)
    os.makedirs(text_folder)

    patterns = ["".join(get_chars(ALPHABETS[a_size], PATTERN_SIZES[p_size])) for _ in range(PATTERN_COUNT)]

    # generate pattern
    with open(patterns_filepath, "w") as f:
        for p in patterns:
            f.write(p)
            f.write("\n")

    # generate texts
    for i in range(TEXT_FILES_COUNT):
        with open(os.path.join(text_folder, "text%d.txt" % i), "w") as f:
            for _ in range(TEXT_LINES_COUNT):
                num_matches = random.randrange(0, int(TEXT_LINE_SIZES[t_size] / float(PATTERN_SIZES[p_size])))
                remaining_chars = TEXT_LINE_SIZES[t_size] - (num_matches * PATTERN_SIZES[p_size])
                line = []

                for _ in range(num_matches):
                    prefix = random.randrange(0, remaining_chars)
                    if prefix:
                        remaining_chars -= prefix
                        line.extend(get_chars(ALPHABETS[a_size], prefix))
                    match = random.choice(patterns)
                    if edit_distance > 0:
                        pos_taken = []
                        pos = 0
                        new_char = ALPHABETS[a_size][0]

                        for _ in range(edit_distance):
                            while (pos in pos_taken):
                                pos = random.randrange(0, len(match) - 1)
                            while (new_char == match[pos]):
                                new_char = random.choice(ALPHABETS[a_size])

                            match = list(match)
                            match[pos] = new_char
                            match = "".join(match)
                            pos_taken.append(pos)
                    line.append(match)

                if remaining_chars > 0:
                    line.extend(get_chars(ALPHABETS[a_size], remaining_chars))

                f.write("".join(line))
                f.write("\n")


if __name__ == "__main__":
    main(docopt(__doc__))
