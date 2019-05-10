// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <thread>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "work_with_text_file.h"
#include <boost/locale/boundary/facets.hpp>
#include <boost/locale/localization_backend.hpp>

using std::ref;
using std::left;
using std::setw;
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

void read_file_into_string(const string &filename, string &str) {
    ifstream stream(filename);
    stringstream buffer;
    buffer << stream.rdbuf();
    str = buffer.str();
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

bool number_compare(pair<string, size_t> &a, pair<string, size_t> &b) {
    return a.second < b.second;
}

bool words_compare(pair<string, size_t> &a, pair<string, size_t> &b) {
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
        if ((*current).will_be_next_data()) {
            (*current).wait_signal();
        }
        if ((*current).try_pop(new_data)) {
            process(current, new_data);
        }
    }
}

void process_result(dispatcher *current) {
    unordered_map<string, size_t> words_map_1;
    unordered_map<string, size_t> words_map_2;
    while ((*current).get_status_of_processing_result()) {
        if ((*current).will_be_next_result()) {
            (*current).wait_signal_result();
        }
        if ((*current).try_pop_result(words_map_1, words_map_2)) {
            for (auto &word:words_map_2) {
                words_map_1[word.first] += word.second;
            }
            (*current).push_result(words_map_1);
        }
    }
}