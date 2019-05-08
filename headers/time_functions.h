//
// Created by Yevhenii on 07/03/2019.
//

#ifndef INC_2_TIME_FUNCTIONS_H
#define INC_2_TIME_FUNCTIONS_H

#include <iostream>
#include <atomic>
#include <typeinfo>
#include <chrono>
#include <sstream>

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

#endif //INC_2_TIME_FUNCTIONS_H
