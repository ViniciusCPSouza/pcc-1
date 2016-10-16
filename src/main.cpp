#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "optionparser.h"

#include "pattern_occurrence.h"
#include "utils.h"

#include "brute_force.h"
#include "kmp.h"
#include "shift_or.h"
#include "wu_mamber.h"
#include "levenshtein.h"


struct Arg: public option::Arg
{
	static void printError(const char* msg1, const option::Option& opt, const char* msg2)
	{
	 std::cerr << "ERROR: " << msg1 << opt.name << msg2;
	}

	static option::ArgStatus NonEmpty(const option::Option& option, bool msg)
	{
	 if (option.arg != 0 && option.arg[0] != 0)
		return option::ARG_OK;

	 if (msg) printError("Option '", option, "' requires a non-empty argument\n");
	 	return option::ARG_ILLEGAL;
	}
};

const std::vector<std::string> algorithms = {"brute_force", "kmp", "shift_or", "wu_mamber", "levenshtein"};
enum optionIndex {HELP, EDIT, PATTERN_FILE, ALGORITHM, COUNT, REPORT_RUNTIME};
const option::Descriptor usage[] =
{
	// INDEX        TYPE  SHORT  LONG               CHECK FUNCTION     HELP TEXT
	{HELP,          0,    "h",   "help",            option::Arg::None, "--help,-h\t Print usage and exit."},
	{EDIT,          0,    "e",   "edit",      	    Arg::NonEmpty,     "--edit,-e e_max\t The maxium edit distance when searching for approximate patterns."},
	{PATTERN_FILE,  0,    "p",   "pattern",         Arg::NonEmpty,     "--pattern,-p patternfile\t A file with the patterns that should be searched."},
	{ALGORITHM,     0,    "a",   "algorithm",       Arg::NonEmpty,     std::string("--algorithm,-a algorithm_name\t Which algorithm to use. Options are: " + utils::join(algorithms, ",")).c_str()},
	{COUNT,         0,    "c",   "count",           option::Arg::None, "--count,-c\t Only print the total number of occurrences found on each file."},
	{REPORT_RUNTIME,0,    "r",   "report-runtime",  option::Arg::None, "--report-runtime,-r\t Write to a csv file the runtime of pattern on each file."},
	{0,0,0,0,0,0}
};


int main(int argc, char** argv)
{
	 std::string algorithm = "";
	 std::vector<data::PatternOccurrence> (*search_function)(std::string,std::string,int) = NULL;
	 int edit = 0;
	 bool count = false;
	 bool report = false;
	 std::string pattern_file = "";
	 std::string pattern = "";
	 std::vector<std::string> text_files;

	 std::vector<std::string> runtimes;
	 std::ostringstream report_line;
	 std::chrono::high_resolution_clock::time_point report_start;
	 std::chrono::high_resolution_clock::time_point report_end;

	 argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
	 option::Stats  stats(usage, argc, argv);
	 option::Option options[stats.options_max], buffer[stats.buffer_max];
	 option::Parser parse(usage, argc, argv, options, buffer);

	 // Parser error
	 if (parse.error()) return 1;

	 // Help
	 if (options[HELP] || argc == 0)
	 {
	 	 std::cout << "USAGE: pmt [options] pattern textfile [textfile...]" << std::endl;
		 option::printUsage(std::cout, usage);
		 return 0;
	 }

	 if (options[EDIT]) edit = std::stoi(options[EDIT].arg);
	 if (options[PATTERN_FILE]) pattern_file = options[PATTERN_FILE].arg;
	 if (options[COUNT]) count = true;
	 if (options[REPORT_RUNTIME]) report = true;

	 if (options[ALGORITHM])
	 {
	 		algorithm = options[ALGORITHM].arg;
	 }
	 else
	 {
			if (edit > 0)
			{
				algorithm = "wu_mamber";
			}
			else
			{
				algorithm = "kmp";
			}
	 }

	 // Set the algorithm search function
	 if (algorithm == "brute_force")
	 {
			search_function = &brute_force::search;
	 }
	 else if (algorithm == "kmp")
	 {
			search_function = &kmp::search;
	 }
	 else if (algorithm == "shift_or")
	 {
			search_function = &shift_or::search;
	 }
	 else if (algorithm == "wu_mamber")
	 {
			search_function = &wu_mamber::search;
	 }
	 else if (algorithm == "levenshtein")
	 {
			search_function = &levenshtein::search;
	 }
	 else
	 {
		std::cerr << "Invalid algorithm '" << algorithm << "'!" << std::endl;
		return 1;
	 }

	 // pattern file was given, all the positional args are text files
	 if (pattern_file != "")
	 {
		 	if (parse.nonOptionsCount() == 0)
		 	{
		 		std::cerr << "Text files not given!" << std::endl;
		 		return 1;
		 	}

		 	for (int i = 0; i < parse.nonOptionsCount(); ++i)
			{
				text_files.push_back(parse.nonOption(i));
			}
	 }
	 // pattern file was NOT given, the first positional argument is the pattern
	 // and all the remaining positional args are text files
	 else {
		 	if (parse.nonOptionsCount() == 0)
		 	{
		 		std::cerr << "Pattern not given!" << std::endl;
		 		return 1;
		 	}
		 	if (parse.nonOptionsCount() < 2) {
		 		std::cerr << "Text file not given!" << std::endl;
		 		return 1;
		 	}

		 	pattern = parse.nonOption(0);
		 	for (int i = 1; i < parse.nonOptionsCount(); ++i)
			{
				text_files.push_back(parse.nonOption(i));
			}
	 }
	 
	// setting up the patterns
	std::vector<std::string> patterns;
	if (pattern_file != "")
	{
		try
		{
			patterns = utils::getPatterns(pattern_file);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Could not read the patterns file! Error:\n" << e.what() << std::endl;
			return 1;
		}
	}
	else {
		patterns.push_back(pattern);
	}
	
	if (count)
	{
		int file_occs = 0;
		int single_file_occs = 0;
		for (std::vector<std::string>::iterator tf = text_files.begin(); tf < text_files.end(); tf++)
		{
			file_occs = 0;
			for (std::vector<std::string>::iterator pat = patterns.begin(); pat < patterns.end(); pat++)
			{
				if (report) report_start = std::chrono::high_resolution_clock::now();
				single_file_occs = search_function(*tf, *pat, edit).size();
				file_occs += single_file_occs;
				if (report)
				{
					report_end = std::chrono::high_resolution_clock::now();

					report_line.str("");
					report_line.clear();

					report_line << pat->length() << "," ;
					report_line << edit << ",";
					report_line << single_file_occs << ",";
					report_line <<  std::chrono::duration_cast<std::chrono::nanoseconds>(report_end - report_start).count() << std::endl;

					runtimes.push_back(report_line.str());
				}
			}
			if (file_occs > 0)
			{
				std::cout << *tf << ":" << file_occs << std::endl;
			}
		}
	}
	else
	{
		std::map<int, bool> lines_to_print;
		for (std::vector<std::string>::iterator tf = text_files.begin(); tf < text_files.end(); tf++)
		{
			lines_to_print.clear();
			for (std::vector<std::string>::iterator pat = patterns.begin(); pat < patterns.end(); pat++)
			{
				if (report) report_start = std::chrono::high_resolution_clock::now();
				std::vector<data::PatternOccurrence> results = search_function(*tf, *pat, edit);
				if (report)
				{
					report_end = std::chrono::high_resolution_clock::now();

					report_line.str("");
					report_line.clear();

					report_line << pat->length() << "," ;
					report_line << edit << ",";
					report_line << results.size() << ",";
					report_line <<  std::chrono::duration_cast<std::chrono::nanoseconds>(report_end - report_start).count() << std::endl;

					runtimes.push_back(report_line.str());
				}

				for (std::vector<data::PatternOccurrence>::iterator it2 = results.begin(); it2 < results.end(); it2++)
				{
					data::PatternOccurrence occ = *it2;
					if (lines_to_print.count(occ.line) == 0)	// first time printing this line
					{
						lines_to_print[occ.line] = true;
					}
				}
			}

			// print the actual lines
			std::ifstream file(*tf);
			std::string line;
			int line_count = 0;
			while (std::getline(file, line))
			{
				// print this line
				if (lines_to_print.count(line_count) != 0) std::cout << line << std::endl;
				line_count++;
			}
		}
	}

	if (report)
	{
		std::ofstream out("runtime.csv");
		out << "pattern_size,edit_distance,matches,runtime" << std::endl;

		for (std::vector<std::string>::iterator it = runtimes.begin(); it != runtimes.end(); it++)
		{
			out << *it;
		}

		out.close();
	}

	return 0;
}
