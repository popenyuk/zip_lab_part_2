// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef INC_5_CONFIGURATION_H
#define INC_5_CONFIGURATION_H

#include <string>

struct config {
    std::string in_file;
    std::string out_by_name;
    std::string out_by_number;
    int indexing_threads;
    int merging_threads;
    int max_number_of_tasks;
};

config read_config(const std::string &filename);

#endif //INC_5_CONFIGURATION_H
