// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com#ifndef _5_MY_QUEUE_H
#ifndef _5_MY_QUEUE_H
#define _5_MY_QUEUE_H


#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class my_queue {
    std::mutex mtx;
    std::queue<T> data;
    std::condition_variable cv;
public:

    size_t get_size();

    bool is_empty();

    void push_data(const T &element);

    T pop_data();

    void send_signal();

    void wait_signal();
};

template<typename T>
size_t my_queue<T>::get_size() {
    return data.size();
}

template<typename T>
bool my_queue<T>::is_empty() {
    return get_size() == 0;
}

template<typename T>
void my_queue<T>::push_data(const T &element) {
    std::lock_guard<std::mutex> lock(mtx);
    data.push(element);
    cv.notify_one();
}

template<typename T>
T my_queue<T>::pop_data() {
    std::unique_lock<std::mutex> lock(mtx);
    T element = data.front();
    data.pop();
    return element;
}

template<typename T>
void my_queue<T>::send_signal() {
    cv.notify_one();
}

template<typename T>
void my_queue<T>::wait_signal() {
    // check this place
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return is_empty(); });
}


#endif //_5_MY_QUEUE_H
