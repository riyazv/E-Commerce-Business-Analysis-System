#ifndef PERFORMANCE_HELPER_HPP
#define PERFORMANCE_HELPER_HPP

#include <chrono>
#include <cstddef>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;

public:
    void begin() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    double endMilliseconds() {
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double,std::milli> d = endTime - startTime;
        return d.count();
    }
};

inline std::size_t estimateTransactionMemory(int count) {
    return count * sizeof(void*) + count * sizeof(std::string) * 6;
}

inline std::size_t estimateReviewMemory(int count) {
    return count * sizeof(void*) + count * sizeof(std::string) * 4;
}

#endif // PERFORMANCE_HELPER_HPP
