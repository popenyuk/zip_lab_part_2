// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef INC_5_ARCHIVE_FUNCTIONS_H
#define INC_5_ARCHIVE_FUNCTIONS_H

#include <vector>
#include <string>
#include "dispatcher.h"

std::vector<std::string> extract_in_memory(const std::string &filename, dispatcher *current = nullptr);

#endif //INC_5_ARCHIVE_FUNCTIONS_H
