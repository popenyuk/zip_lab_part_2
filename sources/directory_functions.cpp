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

void read_txt_files_from_directory(const string &folder, dispatcher *current) {
    for (recursive_directory_iterator it(folder), end; it != end; ++it) {
        if (it->path().extension() == ".ZIP") {
            try {
                extract(it->path().string());
                read_archive_entries(it->path().string(), current);
            } catch (const exception &e) {
            }
        }
        if (it->path().extension() == ".txt") {
            current->push_data(read_file_into_string(it->path().string()));
        }
    }
}