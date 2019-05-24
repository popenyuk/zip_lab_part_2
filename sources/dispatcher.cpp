// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include "dispatcher.h"
#include "archive_functions.h"
#include "directory_functions.h"
#include "work_with_text_file.h"
#include "work_with_text_file.h"
#include "../headers/dispatcher.h"

using std::ref;
using std::cerr;
using std::endl;
using std::mutex;
using std::string;
using std::vector;
using std::thread;
using std::lock_guard;
using std::unique_lock;

dispatcher::dispatcher(const config &conf) : conf_file(conf) {
    indexing_threads.reserve(static_cast<unsigned long>(conf.indexing_threads));
    merging_threads.reserve(static_cast<unsigned long>(conf.merging_threads));
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
    unique_lock<mutex> lock(mtx);
//    if ((get_size() + get_result_size()) > conf_file.max_number_of_tasks) {
//        unique_lock <mutex> lock(mtx);
//        notify_or_not = true;
//        will_new_data_be = false;
//        will_new_result_be = false;
//        cv.notify_all();
//        cv_for_result.notify_all();
//        cv_for_push_data.wait(lock);
//        will_new_data_be = true;
//        will_new_result_be = true;
//    }
    process_data.push(element);
    lock.unlock();
    cv.notify_one();
}

void dispatcher::push_result(const unordered_map<string, size_t> &result) {
    unique_lock<mutex> lock(mtx_for_result);
    result_queue.push(result);
    if (result_queue.size() >= 2) {
        lock.unlock();
        cv_for_result.notify_one();
    }
}

bool dispatcher::try_pop(string &value) {
    lock_guard<mutex> lock(mtx);
    if (!process_data.empty()) {
        value = process_data.front();
        process_data.pop();
//        if ((process_data.size() + result_queue.size()) < (conf_file.max_number_of_tasks / 2) && notify_or_not) {
//            cv_for_push_data.notify_all();
//            notify_or_not = false;
//
//        }
        return true;
    }
    return false;
}

bool dispatcher::try_pop_result(unordered_map<string, size_t> &value1, unordered_map<string, size_t> &value2) {
    lock_guard<mutex> lock(mtx_for_result);
    if (result_queue.size() >= 2) {
        value1 = result_queue.front();
        result_queue.pop();
        value2 = result_queue.front();
        result_queue.pop();
//        if ((process_data.size() + result_queue.size()) < (conf_file.max_number_of_tasks / 2) && notify_or_not) {
//            cv_for_push_data.notify_all();
//            notify_or_not = false;
//        }
        return true;
    }
    return false;
}

void dispatcher::wait_signal() {
    unique_lock<mutex> lock(mtx);
    if (will_new_data_be) {
        cv.wait(lock);
    }
}

void dispatcher::wait_signal_result() {
    unique_lock<mutex> lock(mtx_for_result);
    if (will_new_result_be) {
        cv_for_result.wait(lock);
    }
}

void dispatcher::run() {
    for (int num = 0; num < conf_file.indexing_threads; ++num) {
        indexing_threads.emplace_back(process_the_file, this);
    }
    for (int num = 0; num < conf_file.merging_threads; ++num) {
        merging_threads.emplace_back(process_result, this);
    }
    search_and_add_files(this);
    {
        unique_lock<mutex> lock(mtx);
        will_new_data_be = false;
        lock.unlock();
        cv.notify_all();
    }
    total_end_for_data = true;
    for (auto &indexing_thread:indexing_threads) {
        if (indexing_thread.joinable())
            indexing_thread.join();
    }
    {
        unique_lock<mutex> lock(mtx_for_result);
        total_end_for_result = true;
        will_new_result_be = false;
        lock.unlock();
        cv_for_result.notify_all();
    }
    for (auto &merging_thread:merging_threads) {
        if (merging_thread.joinable())
            merging_thread.join();
    }
}

unordered_map<std::string, size_t> &dispatcher::get_result() {
    lock_guard<mutex> lock(mtx_for_result);
    return result_queue.front();
}

bool dispatcher::get_status_of_processing_data() {
    lock_guard<mutex> lock(mtx);
    return (!process_data.empty()) || !total_end_for_data;
}

bool dispatcher::get_status_of_processing_result() {
    lock_guard<mutex> lock(mtx_for_result);
    return (result_queue.size() != 1) || !total_end_for_result;
}

std::string dispatcher::get_input_file() {
    return conf_file.in_file;
}
