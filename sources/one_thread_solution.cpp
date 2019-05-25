// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include <algorithm>
#include "configuration.h"
#include "time_functions.h"
#include "boost/locale.hpp"
#include "archive_functions.h"
#include "work_with_text_file.h"
#include "directory_functions.h"
#include "directory_function_for_one_thread.h"

using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::locale;
using std::transform;
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

    config conf;
    try {
        conf = read_config(conf_file);
    } catch (invalid_argument &e) {
        cerr << "Invalid argument." << endl;
        exit(-3);
    }

    auto start_time = get_current_time_fenced();

//--------------------------------   Reading file names
    vector<string> files;
    unordered_map<string, size_t> words_map;
    auto extension = find_extension(conf.in_file);
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    if (extension == "zip") {
        files = extract_in_memory(conf.in_file);
    } else if (extension == "txt") {
        string file_in_memory;
        read_file_into_string(conf.in_file, file_in_memory);
        files.push_back(file_in_memory);
    } else if (extension[extension.size() - 1] == '/') {
        words_map = read_txt_files_from_directory(conf.in_file);
    } else {
        cerr << "Wrong file extension." << endl;
        exit(-2);
    }
//--------------------------------   Counting words
    if (extension == "txt" || extension == "zip") {
        vector<string> words;
        for (auto &in_file:files) {
            separate_by_words(in_file, words);
        }
        count_words(words, words_map);
    }

//--------------------------------   Sorting
    auto by_numbers = sort_words(words_map);
    auto by_words = sort_words(words_map, false);

//--------------------------------   Writing to the file
    write_to_file(conf.out_by_number, by_numbers);
    write_to_file(conf.out_by_name, by_words);

//--------------------------------
    auto finish_time = get_current_time_fenced();
    auto time_all_total = finish_time - start_time;

    cout << "Total: " << to_us(time_all_total) << endl;
    return 0;
}