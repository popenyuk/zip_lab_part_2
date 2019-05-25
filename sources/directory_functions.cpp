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
using boost::filesystem::recursive_directory_iterator;

vector<string> read_txt_files_from_directory(const string &folder, dispatcher *current) {
    vector<string> files_in_memory;
    vector<string> new_files;
    string file;
    for (recursive_directory_iterator it(folder), end; it != end; ++it) {
        if (it->path().extension() == ".ZIP") {
            try {
                new_files = extract_in_memory(it->path().string(), current);
                files_in_memory.resize(files_in_memory.size() + new_files.size());
                files_in_memory.insert(files_in_memory.end(), new_files.begin(), new_files.end());
            } catch (...) {
                std::cout << "Err Path: " << it->path() << std::endl;
            }
        }
        if (it->path().extension() == ".txt") {
            read_file_into_string(it->path().string(), file);
            if(current != nullptr){
                current->push_data(file);
            }else{
                files_in_memory.push_back(file);
            }

        }
    }
    return files_in_memory;
}