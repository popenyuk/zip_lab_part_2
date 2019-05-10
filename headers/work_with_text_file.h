// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef INC_5_WORK_WITH_FILE_H
#define INC_5_WORK_WITH_FILE_H

#include <string>
#include "dispatcher.h"
#include "unordered_map"
#include <boost/locale.hpp>

std::string find_extension(const std::string &filename);

void read_file_into_string(const std::string &filename, std::string &str);

void separate_by_words(const std::string &text, std::vector<std::string> &words);

void count_words(std::vector<std::string> &words_vector, std::unordered_map<std::string, size_t> &words);

std::vector<std::pair<std::string, size_t>> sort_words(std::unordered_map<std::string, size_t> &words,
                                                       bool sort_by_number = true);

void write_to_file(const std::string &filename, const std::vector<std::pair<std::string, size_t>> &words);

void process(dispatcher *current, const std::string &data);

void process_the_file(dispatcher *current);

void process_result(dispatcher *current);

#endif //INC_5_WORK_WITH_FILE_H
