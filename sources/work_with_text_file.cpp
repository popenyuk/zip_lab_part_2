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

unordered_map<string, size_t> merge_results(vector<unordered_map<string, size_t >> &r) {
    unordered_map<string, size_t> final;
    for (auto &i: r) {
        for (auto &j: i) {
            final[j.first] += j.second;
        }
    }
    return final;
}

void count_words_multi_thread(vector<string> &words_vector, vector<unordered_map<string, size_t>> &results, int start,
                              int end, int id) {
    unordered_map<string, size_t> counted;
    for (auto i = start; i < end; i++)
        counted[fold_case(normalize(words_vector[i], norm_nfd))]++;
    results[id] = counted;
}

void run_multi_thread(int threads_num, vector<string> &words_vector, unordered_map<string, size_t> &words_map) {
    vector<unordered_map<string, size_t>> results;
    vector<thread> threads;
    threads.reserve(static_cast<unsigned long>(threads_num));

    if (threads_num > words_vector.size() || threads_num < 1)
        threads_num = static_cast<int>(words_vector.size());

    size_t value_per_thread = words_vector.size() / threads_num;
    size_t start_value = 0;
    size_t end_value = start_value + value_per_thread;

    for (int i = 0; i < threads_num; ++i)
        results.emplace_back();

    for (int i = 0; i < threads_num; i++) {
        try {
            threads.emplace_back(count_words_multi_thread, ref(words_vector), ref(results), start_value, end_value, i);
        } catch (exception &ex) {
            cout << "Error: " << ex.what() << endl;
            throw;
        }

        start_value += value_per_thread;
        end_value += value_per_thread;

        if (i == threads_num - 2)
            end_value = words_vector.size();
    }
    for (int i = 0; i < threads_num; ++i) {
        threads[i].join();
    }
    threads.clear();
    words_map = merge_results(results);
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