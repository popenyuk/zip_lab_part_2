// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef INC_5_ARCHIVE_FUNCTIONS_H
#define INC_5_ARCHIVE_FUNCTIONS_H

#include <vector>
#include <string>
<<<<<<< HEAD
#include "dispatcher.h"
=======
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375

int copy_data(struct archive *ar, struct archive *aw);

void extract(const std::string &filename);

<<<<<<< HEAD
void read_archive_entries(const std::string &path, dispatcher *current);
=======
std::vector<std::string> read_archive_entries(const std::string &path);
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375

#endif //INC_5_ARCHIVE_FUNCTIONS_H
