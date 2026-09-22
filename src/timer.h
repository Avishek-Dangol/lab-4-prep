#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <cstdint>  // uint64_t

class Timer {
public:
    using Nanos = std::chrono::nanoseconds;
    using Micros = std::chrono::microseconds;
    using Millis = std::chrono::milliseconds;
    using Seconds = std::chrono::seconds;
    using Minutes = std::chrono::minutes;
    using Hours = std::chrono::hours;

    Timer() : start_(std::chrono::steady_clock::now()) {}

    void restart() { start_ = std::chrono::steady_clock::now(); }

    // Returns the elapsed time in the specified duration type T since the last restart or
    // construction.
    template <typename T>
    uint64_t click() {
        auto now = std::chrono::steady_clock::now();
        uint64_t elapsed =
            static_cast<uint64_t>(std::chrono::duration_cast<T>(now - start_).count());
        start_ = now;
        return elapsed;
    }

    // returns the number of microseconds since the Timer was last clicked/restarted/constructed,
    // whichever has happened most recently.
    template <typename T>
    uint64_t glance() const {  // const because it does not change the timer
        auto now = std::chrono::steady_clock::now();
        return static_cast<uint64_t>(std::chrono::duration_cast<T>(now - start_).count());
    }

private:
    std::chrono::steady_clock::time_point start_;
};

#endif  // TIMER_H
