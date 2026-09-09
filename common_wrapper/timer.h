#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

// A simple stopwatch-style timer class
class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

public:
    // Starts the timer
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    // Stops the timer and returns the elapsed time in seconds
    double stop() {
        end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        return elapsed.count();
    }
};

#endif // TIMER_H