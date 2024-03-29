// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com#ifndef _5_DISPATCHER_H
#ifndef _5_DISPATCHER_H
#define _5_DISPATCHER_H

#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include "configuration.h"
#include <condition_variable>

using std::unordered_map;

class dispatcher {
    std::mutex mtx;
    config conf_file;
    std::mutex mtx_for_result;
    std::condition_variable cv;
    bool notify_or_not = false;
    bool will_new_data_be = true;
    bool will_new_result_be = true;
    bool total_end_for_data = false;
    bool total_end_for_result = false;
    std::queue<std::string> process_data;
    std::condition_variable cv_for_result;
    std::condition_variable cv_for_push_data;
    std::vector<std::thread> merging_threads;
    std::vector<std::thread> indexing_threads;
    std::queue<unordered_map<std::string, size_t >> result_queue;

public:
    explicit dispatcher(const config &conf);

    size_t get_size();

    size_t get_result_size();

    std::string get_input_file();

    void push_data(const std::string &element);

    void push_result(const unordered_map<std::string, size_t> &result);

    bool try_pop(std::string &value);

    bool try_pop_result(unordered_map<std::string, size_t> &value1, unordered_map<std::string, size_t> &value2);

    void run();

    unordered_map<std::string, size_t> &get_result();

    void wait_signal();

    void wait_signal_result();

    bool get_status_of_processing_data();

    bool get_status_of_processing_result();
};

#endif //_5_DISPATCHER_H
