#!/usr/bin/env bash

EXACT_ALGORITHMS=("kmp" "shift_or")
FUZZY_ALGORITHMS=("levenshtein" "wu_mamber")

DATA_FOLDER="test_data"
TEXT_FOLDER="txt"
PATTERN_FILE="patterns.txt"
OUTPUT_FOLDER="test_results"

PMT="bin/pmt"

if [ ! -f "$PMT" ]; then
  # install the tool correctly
	./install.sh || exit 1
fi

for dataset in $DATA_FOLDER/*; do
	dataset_name=`basename "$dataset"`
	# gt_folder="$OUTPUT_FOLDER/$dataset_name/gt"

	# # if the ground truth wasn't generated it, do it
	# if [ ! "$(ls -A $gt_folder)" ]
	# then
	#   mkdir -p "$gt_folder"

	#   cd "$dataset/$TEXT_FOLDER/"

	#   for text_file in *.txt; do
	#   	echo -n $text_file
	#   	echo -n ":"
	#   	echo `grep -o -f "../$PATTERN_FILE" $text_file | wc -l`
	#   done

	#   cd "../../.."

	# fi

	
done
