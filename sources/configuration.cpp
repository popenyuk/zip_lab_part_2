//
// Created by Yevhenii on 23/04/2019.
//

#include "../headers/configuration.h"
#include <iostream>

config read_config(const std::string &filename) {
    config conf{};
    std::string s;
    std::string s1;
    std::string s2;
    std::ifstream infile(filename);
    std::vector<std::string> conf_vector;

    for (int i = 0; i < 3; ++i) {
        infile >> s;
        conf_vector.push_back(s.substr(s.find('"') + 1, s.find_last_not_of('"') - s.find('"')));
    }
    infile >> s;
    s1 = s.substr(s.find('=') + 1, s.find('\\'));
    s2 = s.substr(s.find('=') + 1, s.find('\\'));

    conf.in_file = conf_vector[0];
    conf.out_by_name = conf_vector[1];
    conf.out_by_number = conf_vector[2];
    conf.indexing_threads = std::stoi(s1);
    conf.merging_threads = std::stoi(s2);
    return conf;
}
