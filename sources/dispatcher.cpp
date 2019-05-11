// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "dispatcher.h"
#include "work_with_text_file.h"

using std::ref;
using std::mutex;
using std::string;
using std::vector;
using std::thread;
using std::lock_guard;
using std::unique_lock;

dispatcher::dispatcher(const config &conf, const vector<string> &input) : conf_file(conf), input_data(input) {
    lock_guard<mutex> lock(mtx);
    lock_guard<mutex> lck(mtx_for_result);
    indexing_threads.reserve(conf.indexing_threads);
    merging_threads.reserve(conf.merging_threads);
}

size_t dispatcher::get_size() {
    lock_guard<mutex> lock(mtx);
    return process_data.size();
}

size_t dispatcher::get_result_size() {
    lock_guard<mutex> lock(mtx_for_result);
    return result_queue.size();
}

void dispatcher::push_data(const string &element) {
    lock_guard<mutex> lock(mtx);
    process_data.push(element);
    cv.notify_one();
}

void dispatcher::push_result(const unordered_map<string, size_t> &result) {
    lock_guard<mutex> lock(mtx_for_result);
    result_queue.push(result);
    if (result_queue.size() >= 2) {
        cv_for_result.notify_one();
    }
}

bool dispatcher::try_pop(string &value) {
    if (get_size()) {
        lock_guard<mutex> lock(mtx);
        value = process_data.front();
        process_data.pop();
        return true;
    }
    return false;
}

bool dispatcher::try_pop_result(unordered_map<string, size_t> &value1, unordered_map<string, size_t> &value2) {
    if (get_result_size() >= 2) {
        lock_guard<mutex> lock(mtx_for_result);
        value1 = result_queue.front();
        result_queue.pop();
        value2 = result_queue.front();
        result_queue.pop();
        return true;
    }
    return false;
}

void dispatcher::wait_signal() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock);
}

void dispatcher::wait_signal_result() {
    unique_lock<mutex> lock(mtx_for_result);
    cv_for_result.wait(lock);
}

void dispatcher::run() {
    string string_file;
    for (int num = 0; num < conf_file.indexing_threads; ++num) {
        indexing_threads.emplace_back(process_the_file, this);
    }
    for (int num = 0; num < conf_file.merging_threads; ++num) {
        merging_threads.emplace_back(process_result, this);
    }
    for (auto &in_file:input_data) {
        read_file_into_string(in_file, string_file);
        push_data(string_file);
    }
    will_new_data_be = false;
    cv.notify_all();
    for (auto &indexing_thread:indexing_threads) {
        indexing_thread.join();
    }
    will_new_result_be = false;
    cv_for_result.notify_all();
    for (auto &merging_thread:merging_threads) {
        merging_thread.join();
    }
}

unordered_map<std::string, size_t> &dispatcher::get_result() {
    lock_guard<mutex> lock(mtx_for_result);
    return result_queue.front();
}

bool dispatcher::get_status_of_processing_data() {
    return will_new_data_be || get_size();
}

bool dispatcher::get_status_of_processing_result() {
    return will_new_result_be || (get_result_size() != 1);
}

bool dispatcher::will_be_next_data() {
    return will_new_data_be;
}

bool dispatcher::will_be_next_result() {
    return will_new_result_be;
}