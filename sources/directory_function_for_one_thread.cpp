// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include "archive_functions.h"
#include "boost/filesystem.hpp"
#include "directory_functions.h"
#include "work_with_text_file.h"

using std::vector;
using std::string;
using std::exception;
using std::unordered_map;
using boost::filesystem::recursive_directory_iterator;

unordered_map<string, size_t> read_txt_files_from_directory(const string &folder) {
    string file;
    vector<string> new_files;
    vector<string> files_in_memory;
    unordered_map<string, size_t> words_map;
    for (recursive_directory_iterator it(folder), end; it != end; ++it) {
        if (it->path().extension() == ".ZIP") {
            try {
                new_files = extract_in_memory(it->path().string());
                for (auto &in_file:new_files) {
                    separate_by_words(in_file, files_in_memory);
                }
                count_words(files_in_memory, words_map);

            } catch (...) {
                std::cout << "Err Path: " << it->path() << std::endl;
            }
        }
        if (it->path().extension() == ".txt") {
            read_file_into_string(it->path().string(), file);
            separate_by_words(file, files_in_memory);
            count_words(files_in_memory, words_map);
        }
        files_in_memory.clear();
    }
    return words_map;
}