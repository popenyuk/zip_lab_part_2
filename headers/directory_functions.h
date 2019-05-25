// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com#ifndef _5_DIRECTORY_FUNCTIONS_H
#ifndef _5_DIRECTORY_FUNCTIONS_H
#define _5_DIRECTORY_FUNCTIONS_H

#include <string>
#include <vector>
#include "dispatcher.h"

std::vector<std::string> read_txt_files_from_directory(const std::string &folder, dispatcher *current = nullptr);

#endif //_5_DIRECTORY_FUNCTIONS_H
