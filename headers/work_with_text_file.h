//
// Created by Yevhenii on 23/04/2019.
//

#ifndef INC_5_WORK_WITH_FILE_H
#define INC_5_WORK_WITH_FILE_H

#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <boost/locale.hpp>
#include <boost/locale/boundary/facets.hpp>
#include <boost/locale/localization_backend.hpp>

std::string find_extension(const std::string& filename);
void read_file_into_string(const std::string& filename, std::string& str);
void separate_by_words(const std::string& text, std::vector<std::string>& words);
void count_words(std::vector<std::string>& words_vector, std::unordered_map<std::string, size_t>& words);
std::vector<std::pair<std::string, size_t>> sort_words(std::unordered_map<std::string, size_t>& words, bool sort_by_number=true);
void write_to_file(const std::string& filename, const std::vector<std::pair<std::string, size_t>>& words);
void run_multi_thread(int threads_num, std::vector<std::string> &words_vector, std::unordered_map<std::string, size_t>& words_map);


#endif //INC_5_WORK_WITH_FILE_H
