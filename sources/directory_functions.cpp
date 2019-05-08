// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include "directory_functions.h"

using std::vector;
using std::string;
using namespace boost::filesystem;

vector<string> read_txt_files_from_directory(const string &folder) {
    vector<string> files;
    for (recursive_directory_iterator it(folder), end; it != end; ++it) {
        if (it->path().extension() == ".txt") {
            files.push_back((*it).path().string());
        }
    }
    return files;
}