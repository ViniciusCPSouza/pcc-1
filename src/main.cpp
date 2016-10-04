#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "optionparser.h"

#include "brute_force.h"
#include "utils.h"


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

const std::vector<std::string> algorithms = {"brute_force"};
enum SearchType {EXACT, APPROXIMATED};
enum optionIndex {HELP, EDIT, PATTERN_FILE, ALGORITHM, COUNT};
const option::Descriptor usage[] =
{
	// PARSER INDEX   TYPE  SHORT  LONG         CHECK FUNCTION     HELP TEXT
	{HELP,            0,    "h" ,  "help",      option::Arg::None, "--help,-h\t Print usage and exit."},
	{EDIT,            0,    "e",   "edit",      Arg::NonEmpty,     "--edit,-e e_max\t The maxium edit distance when searching for approximate patterns."},
	{PATTERN_FILE,    0,    "p",   "pattern",   Arg::NonEmpty,     "--pattern,-p patternfile\t A file with the patterns that should be searched."},
	{ALGORITHM,       0,    "a",   "algorithm", Arg::NonEmpty,     std::string("--algorithm,-a algorithm_name\t Which algorithm to use. Options are: " + utils::join(algorithms, ",")).c_str()},
	{COUNT,           0,    "c",   "count",     option::Arg::None, "--count,-c\t Only print the total number of occurrences found on each file."},
	{0,0,0,0,0,0}
};


int main(int argc, char** argv)
{
   std::string algorithm = "brute_force";
   std::vector<PatternOccurrence> (*search_function)(std::string,std::string,int) = NULL;
   int edit = 0;
   bool count = false;
   std::string pattern_file = "";
   SearchType search_type = EXACT;
   std::string pattern = "";
   std::vector<std::string> text_files;

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
   if (options[ALGORITHM]) algorithm = options[ALGORITHM].arg;
   if (options[COUNT])
   {
	 	count = true;
	 	search_type = APPROXIMATED;
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

   if (parse.nonOptionsCount() < 2)
   {
   	std::cerr << "" << std::endl;
   }

   // DEBUG: print args
   std::cout << "#### ARGS ####" << std::endl;
   std::cout << "Pattern: " << pattern << std::endl;
   std::cout << "Count: " << count << std::endl;
   std::cout << "Search Type: " << search_type << std::endl;
   std::cout << "Edit: " << edit << std::endl;
   std::cout << "Algorithm: " << algorithm << std::endl;
   std::cout << "Pattern File: " << pattern_file << std::endl;
   std::cout << "Text Files: " << std::endl;
   for (std::vector<std::string>::iterator it = text_files.begin(); it < text_files.end(); it++)
   {
   	std::cout << "\t" << *it << std::endl;
   }

   return 0;
}
