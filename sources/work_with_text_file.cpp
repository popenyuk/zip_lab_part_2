//
// Created by Yevhenii on 23/04/2019.
//


#include "work_with_text_file.h"

using namespace boost::locale;
using namespace boost::locale::boundary;

std::string find_extension(const std::string &filename) {
    return filename.substr(filename.find_last_of('.') + 1, filename.length());
}

void read_file_into_string(const std::string &filename, std::string &str) {
    std::ifstream stream(filename);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    str = buffer.str();
}

void write_to_file(const std::string &filename, const std::vector<std::pair<std::string, size_t>> &words) {
    std::ofstream my_file;
    my_file.open(filename);
    for (const auto &i: words)
        my_file << std::left << std::setw(15) << i.first << ":  " << i.second << std::endl;
}

void separate_by_words(const std::string &text, std::vector<std::string> &words) {
    ssegment_index map(word, text.begin(), text.end());
    map.rule(word_letters);
    for (ssegment_index::iterator it = map.begin(), e = map.end(); it != e; ++it)
        words.emplace_back(*it);
}

void count_words(std::vector<std::string> &words_vector, std::unordered_map<std::string, size_t> &words) {
    for (const auto &w: words_vector)
        words[fold_case(normalize(w, norm_nfd))]++;
}

std::unordered_map<std::string, size_t> merge_results(std::vector<std::unordered_map<std::string, size_t >> &r) {
    std::unordered_map<std::string, size_t> final;
    for (auto &i: r) {
        for (auto &j: i) {
            final[j.first] += j.second;
        }
    }
    return final;
}

void count_words_multi_thread(std::vector<std::string> &words_vector,
                              std::vector<std::unordered_map<std::string, size_t>> &results,
                              int start, int end, std::mutex &m, int id) {
    std::unordered_map<std::string, size_t> counted;
    for (auto i = start; i < end; i++)
        counted[fold_case(normalize(words_vector[i], norm_nfd))]++;
    results[id] = counted;
}

void run_multi_thread(int threads_num, std::vector<std::string> &words_vector,
                      std::unordered_map<std::string, size_t> &words_map) {
    std::vector<std::unordered_map<std::string, size_t>> results;
    std::vector<std::thread> threads;
    threads.reserve(static_cast<unsigned long>(threads_num));
    std::mutex m;

    if (threads_num > words_vector.size() || threads_num < 1)
        threads_num = static_cast<int>(words_vector.size());

    size_t value_per_thread = words_vector.size() / threads_num;
    size_t start_value = 0;
    size_t end_value = start_value + value_per_thread;

    for (int i = 0; i < threads_num; ++i)
        results.emplace_back();

    for (int i = 0; i < threads_num; i++) {
        try {
            threads.emplace_back(
                    count_words_multi_thread,
                    std::ref(words_vector),
                    std::ref(results),
                    start_value, end_value,
                    std::ref(m), i
            );
        } catch (std::exception &ex) {
            std::cout << "Error: " << ex.what() << std::endl;
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

bool number_compare(std::pair<std::string, size_t> &a, std::pair<std::string, size_t> &b) {
    return a.second < b.second;
}

bool words_compare(std::pair<std::string, size_t> &a, std::pair<std::string, size_t> &b) {
    return a.first < b.first;
}

std::vector<std::pair<std::string, size_t>>
sort_words(std::unordered_map<std::string, size_t> &words, bool sort_by_number) {
    std::vector<std::pair<std::string, size_t>> elements(words.begin(), words.end());
    sort_by_number ? std::sort(elements.begin(), elements.end(), number_compare) :
    std::sort(elements.begin(), elements.end(), words_compare);
    return elements;
}