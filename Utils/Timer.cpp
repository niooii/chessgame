//
// Created by niooi on 8/19/23.
//

#include "Timer.h"

Timer::Timer()
{
    last = CurrentMicros();
}

unsigned long Timer::CurrentMicros() {
    std::chrono::duration value = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch());
    return value.count();
}

double Timer::ElapsedSeconds() {
    return ElapsedMicros()/1000000.0;
}

double Timer::ElapsedMillis() {
    return ElapsedMicros()/1000.0;
}

unsigned long Timer::ElapsedMicros() {
    return (CurrentMicros()-last);
}

void Timer::Reset() {
    last = CurrentMicros();
}
