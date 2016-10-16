#!/usr/bin/env bash

EXACT_ALGORITHMS=("brute_force" "kmp" "shift_or")
FUZZY_ALGORITHMS=("wu_mamber" "levenshtein")

DATA_FOLDER="datasets"
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
	outpur_folder="$OUTPUT_FOLDER/$dataset_name/"

	mkdir -p "$outpur_folder"

	echo "Dataset: ${dataset_name}"

	# exact matching
	if [[ "${dataset_name}" == *E0 ]]
	then
		echo "EXACT!"
		for a in "${EXACT_ALGORITHMS[@]}"
		do
		   echo "Running '$a'"
		   ./bin/pmt -a "$a" --count --report-runtime --pattern "$dataset/patterns.txt" $dataset/txt/* > output.txt

		   algorithm_folder="$outpur_folder/$a"

		   mkdir -p "$algorithm_folder"
		   mv runtime.csv "$algorithm_folder/"
		   mv output.txt "$algorithm_folder/"
		done
	# fuzzy matching
	else
		echo "FUZZY!"
		for a in "${FUZZY_ALGORITHMS[@]}"
		do
		   echo "Running '$a'"
		   ./bin/pmt -a "$a" --edit "${dataset: -1}" --count --report-runtime --pattern "$dataset/patterns.txt" $dataset/txt/* > output.txt

		   algorithm_folder="$outpur_folder/$a"

		   mkdir -p "$algorithm_folder"
		   mv runtime.csv "$algorithm_folder/"
		   mv output.txt "$algorithm_folder/"
		done
	fi
	
done
