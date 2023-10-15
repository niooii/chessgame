//
// Created by niooi on 8/19/23.
//

#pragma once
#include <chrono>

class Timer {
private:
    unsigned long last;
    unsigned long CurrentMicros();

public:
    Timer();
    double ElapsedSeconds();
    double ElapsedMillis();
    unsigned long ElapsedMicros();
    void Reset();
};