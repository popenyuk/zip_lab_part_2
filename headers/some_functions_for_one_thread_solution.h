// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef _5_SOME_FUNCTIONS_FOR_ONE_THREAD_SOLUTION_H
#define _5_SOME_FUNCTIONS_FOR_ONE_THREAD_SOLUTION_H

#include <string>
#include <vector>

std::vector<std::string> read_archive_entries_one_thread(const std::string &path);

std::vector<std::string> read_txt_files_from_directory_one_thread(const std::string &folder);

#endif //_5_SOME_FUNCTIONS_FOR_ONE_THREAD_SOLUTION_H
