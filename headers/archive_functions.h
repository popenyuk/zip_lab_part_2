// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef INC_5_ARCHIVE_FUNCTIONS_H
#define INC_5_ARCHIVE_FUNCTIONS_H

#include <vector>
#include <string>
#include "dispatcher.h"

int copy_data(struct archive *ar, struct archive *aw);

void extract(const std::string &filename);

void read_archive_entries(const std::string &path, dispatcher *current);

#endif //INC_5_ARCHIVE_FUNCTIONS_H
