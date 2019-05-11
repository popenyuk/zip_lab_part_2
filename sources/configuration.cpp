// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <fstream>
#include <iostream>
#include "configuration.h"

using std::stoi;
using std::string;
using std::vector;
using std::ifstream;

config read_config(const string &filename) {
    config conf{};
    string s;
    string s1;
    string s2;
    ifstream infile(filename);
    vector<string> conf_vector;

    for (int i = 0; i < 3; ++i) {
        infile >> s;
        conf_vector.push_back(s.substr(s.find('"') + 1, s.find_last_not_of('"') - s.find('"')));
    }
    infile >> s;
    s1 = s.substr(s.find('=') + 1, s.find('\\'));
    infile >> s;
    s2 = s.substr(s.find('=') + 1, s.find('\\'));

    conf.in_file = conf_vector[0];
    conf.out_by_name = conf_vector[1];
    conf.out_by_number = conf_vector[2];
    conf.indexing_threads = stoi(s1);
    conf.merging_threads = stoi(s2);
    return conf;
}
