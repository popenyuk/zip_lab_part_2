// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef _5_DIRECTORY_FUNCTION_FOR_ONE_THREAD_H
#define _5_DIRECTORY_FUNCTION_FOR_ONE_THREAD_H

#include <string>
#include <vector>

std::unordered_map<std::string, size_t> read_txt_files_from_directory(const std::string &folder);

#endif //_5_DIRECTORY_FUNCTION_FOR_ONE_THREAD_H
