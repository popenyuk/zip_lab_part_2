// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <algorithm>
#include "configuration.h"
#include "time_functions.h"
#include "archive_functions.h"
#include "work_with_text_file.h"


using std::endl;
using std::cerr;
using std::cout;
using std::string;
using std::vector;
using std::locale;
using std::unordered_map;
using std::invalid_argument;
using boost::locale::generator;

int main(int argc, char *argv[]) {
    generator gen;
    locale loc = gen.generate("en_US.UTF-8");
    locale::global(loc);
    cout.imbue(loc);

    string conf_file;
    if (argc < 2) {
        conf_file = "../config.dat";
    } else if (argc > 2) {
        cerr << "Wrong number of arguments. Usage: <config_filename>";
        exit(-1);
    } else {
        conf_file = argv[1];
    }

    string in_file;
    config conf;
    try {
        conf = read_config(conf_file);
    } catch (invalid_argument &e) {
        cerr << "Invalid argument." << endl;
        exit(-3);
    }

    auto start_time = get_current_time_fenced();
//--------------------------------   Reading file in memory
    auto extension = find_extension(conf.in_file);
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    if (extension == "zip") {
        extract(conf.in_file);
        read_file_into_string(read_archive_entries(conf.in_file)[0], in_file);
    } else if (extension == "txt") {
        read_file_into_string(conf.in_file, in_file);
    } else {
        cerr << "Wrong file extension." << endl;
        exit(-2);
    }
    vector<string> words;
    separate_by_words(in_file, words);
//--------------------------------   Counting words
    unordered_map<string, size_t> words_map;
    run_multi_thread(conf.indexing_threads + conf.merging_threads, words, words_map);
//--------------------------------   Sorting
    auto by_numbers = sort_words(words_map);
    auto by_words = sort_words(words_map, false);
//--------------------------------
    auto finish_time = get_current_time_fenced();
//--------------------------------   Writing to the file
    write_to_file(conf.out_by_number, by_numbers);
    write_to_file(conf.out_by_name, by_words);
//--------------------------------
    auto time_all_total = finish_time - start_time;

    cout << "Total time: " << to_us(time_all_total) << endl;

    return 0;
}