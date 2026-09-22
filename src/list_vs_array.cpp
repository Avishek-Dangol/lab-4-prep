#include <cstddef>  // size_t
#include <iostream>
#include <list>
#include <random>
#include <vector>

#include "timer.h"

constexpr size_t SIZE = 16000000;

int main() {
    std::mt19937_64 rng(0);
    Timer timer;

    std::list<uint64_t> lst;
    timer.restart();
    for (size_t i = 0; i < SIZE; ++i) {
        lst.push_back(rng());
    }
    uint64_t listInsertUs = timer.click<Timer::Micros>();

    std::vector<uint64_t> vec;
    rng.seed(0);
    timer.restart();
    for (size_t i = 0; i < SIZE; ++i) {
        vec.push_back(rng());
    }
    uint64_t vectorInsertUs = timer.click<Timer::Micros>();

    std::vector<uint64_t> reserved;
    reserved.reserve(SIZE);
    rng.seed(0);
    timer.restart();
    for (size_t i = 0; i < SIZE; ++i) {
        reserved.push_back(rng());
    }
    uint64_t reservedInsertUs = timer.click<Timer::Micros>();

    std::cout << "List insert time: " << listInsertUs << " microseconds" << std::endl;
    std::cout << "Vector insert time: " << vectorInsertUs << " microseconds" << std::endl;
    std::cout << "Reserved vector insert time: " << reservedInsertUs << " microseconds"
              << std::endl;

    // Sum and time the sum of the elements in the list and vector
    uint64_t sum = 0;
    timer.restart();
    for (uint64_t value : lst) {
        sum += value;
    }
    uint64_t listSumUs = timer.click<Timer::Micros>();
    std::cout << "List sum: " << sum << " " << listSumUs << " microseconds" << std::endl;

    sum = 0;
    timer.restart();
    for (uint64_t value : vec) {
        sum += value;
    }
    uint64_t vectorSumUs = timer.click<Timer::Micros>();
    std::cout << "Vector sum: " << sum << " " << vectorSumUs << " microseconds" << std::endl;

    return 0;
}
