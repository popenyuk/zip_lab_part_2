// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <thread>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
<<<<<<< HEAD
#include "archive_functions.h"
#include "work_with_text_file.h"
#include "directory_functions.h"
=======
#include "work_with_text_file.h"
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375
#include <boost/locale/boundary/facets.hpp>
#include <boost/locale/localization_backend.hpp>

using std::ref;
using std::left;
using std::setw;
<<<<<<< HEAD
using std::cerr;
=======
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375
using std::endl;
using std::pair;
using std::cout;
using std::string;
using std::vector;
using std::thread;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::stringstream;
using std::unordered_map;
using boost::locale::norm_nfd;
using boost::locale::fold_case;
using boost::locale::boundary::word;
using boost::locale::boundary::word_letters;
using boost::locale::boundary::ssegment_index;

string find_extension(const string &filename) {
    return filename.substr(filename.find_last_of('.') + 1, filename.length());
}

<<<<<<< HEAD
string read_file_into_string(const string &filename) {
    ifstream stream(filename);
    stringstream buffer;
    buffer << stream.rdbuf();
    return buffer.str();
=======
void read_file_into_string(const string &filename, string &str) {
    ifstream stream(filename);
    stringstream buffer;
    buffer << stream.rdbuf();
    str = buffer.str();
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375
}

void write_to_file(const string &filename, const vector<pair<string, size_t>> &words) {
    ofstream my_file;
    my_file.open(filename);
    for (const auto &i: words)
        my_file << left << setw(15) << i.first << ":  " << i.second << endl;
}

void separate_by_words(const string &text, vector<string> &words) {
    ssegment_index map(word, text.begin(), text.end());
    map.rule(word_letters);
    for (ssegment_index::iterator it = map.begin(), e = map.end(); it != e; ++it)
        words.emplace_back(*it);
}

void count_words(vector<string> &words_vector, unordered_map<string, size_t> &words) {
    for (const auto &w: words_vector)
        words[fold_case(normalize(w, norm_nfd))]++;
}

const bool number_compare(pair<string, size_t> &a, pair<string, size_t> &b) {
    return a.second < b.second;
}

const bool words_compare(pair<string, size_t> &a, pair<string, size_t> &b) {
    return a.first < b.first;
}

vector<pair<string, size_t>> sort_words(unordered_map<string, size_t> &words, bool sort_by_number) {
    vector<pair<string, size_t>> elements(words.begin(), words.end());
    sort_by_number ? sort(elements.begin(), elements.end(), number_compare) :
    sort(elements.begin(), elements.end(), words_compare);
    return elements;
}

void process(dispatcher *current, const string &inputed_data) {
    vector<string> words;
    unordered_map<string, size_t> words_map;
    separate_by_words(inputed_data, words);
    count_words(words, words_map);
    (*current).push_result(words_map);
}

void process_the_file(dispatcher *current) {
    string new_data;
    while ((*current).get_status_of_processing_data()) {
<<<<<<< HEAD
        (*current).wait_signal();
=======
        if ((*current).will_be_next_data()) {
            (*current).wait_signal();
        }
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375
        if ((*current).try_pop(new_data)) {
            process(current, new_data);
        }
    }
}

void process_result(dispatcher *current) {
    unordered_map<string, size_t> words_map_1;
    unordered_map<string, size_t> words_map_2;
    while ((*current).get_status_of_processing_result()) {
<<<<<<< HEAD
        (*current).wait_signal_result();
=======
        if ((*current).will_be_next_result()) {
            (*current).wait_signal_result();
        }
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375
        if ((*current).try_pop_result(words_map_1, words_map_2)) {
            for (auto &word:words_map_2) {
                words_map_1[word.first] += word.second;
            }
            (*current).push_result(words_map_1);
        }
    }
<<<<<<< HEAD
}


void search_and_add_files(dispatcher *current) {
    //--------------------------------   Reading file in memory
    auto extension = find_extension(current->get_input_file());
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    if (extension == "zip") {
        extract(current->get_input_file());
        read_archive_entries(current->get_input_file(), current);
    } else if (extension == "txt") {
        current->push_data(current->get_input_file());
    } else if (extension[extension.size() - 1] == '/') {
        read_txt_files_from_directory(current->get_input_file(), current);
    } else {
        cerr << "Wrong file extension." << endl;
        exit(-2);
    }
=======
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375
}