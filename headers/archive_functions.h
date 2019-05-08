//
// Created by Yevhenii on 23/04/2019.
//

#ifndef INC_5_ARCHIVE_FUNCTIONS_H
#define INC_5_ARCHIVE_FUNCTIONS_H
#include <vector>
#include <string>
#include <iostream>
#include <archive.h>
#include <archive_entry.h>

int copy_data(struct archive *ar, struct archive *aw);
void extract(const std::string& filename);
std::vector<std::string> read_archive_entries(const std::string& path);

#endif //INC_5_ARCHIVE_FUNCTIONS_H
