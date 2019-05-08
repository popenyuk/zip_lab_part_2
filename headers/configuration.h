//
// Created by Yevhenii on 23/04/2019.
//

#ifndef INC_5_CONFIGURATION_H
#define INC_5_CONFIGURATION_H

#include <vector>
#include <fstream>

struct config{
    std::string in_file;
    std::string out_by_name;
    std::string out_by_number;
    int indexing_threads;
    int merging_threads;
};

config read_config(const std::string& filename);

#endif //INC_5_CONFIGURATION_H
