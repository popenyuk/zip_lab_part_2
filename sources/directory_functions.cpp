// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
<<<<<<< HEAD
#include <iostream>
#include "archive_functions.h"
#include "boost/filesystem.hpp"
#include "directory_functions.h"
#include "work_with_text_file.h"
=======
#include "boost/filesystem.hpp"
#include "directory_functions.h"
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375

using std::vector;
using std::string;
using boost::filesystem::recursive_directory_iterator;

<<<<<<< HEAD
void read_txt_files_from_directory(const string &folder, dispatcher *current) {
    for (recursive_directory_iterator it(folder), end; it != end; ++it) {
        if(it->path().extension() == ".ZIP"){
            extract(it->path().string());
            read_archive_entries(it->path().string(), current);
        }
        if (it->path().extension() == ".txt") {
            current->push_data(read_file_into_string(it->path().string()));
        }
    }
=======
vector<string> read_txt_files_from_directory(const string &folder) {
    vector<string> files;
    for (recursive_directory_iterator it(folder), end; it != end; ++it) {
        if (it->path().extension() == ".txt") {
            files.push_back((*it).path().string());
        }
    }
    return files;
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375
}