#include <iostream>
#include "Timer.h"

CountdownTimer::CountdownTimer(int seconds) : seconds_remaining(seconds) {
        }

CountdownTimer::CountdownTimer() : CountdownTimer(0){}

void CountdownTimer::set_time(int seconds){
            seconds_remaining = seconds;

}

void CountdownTimer::Start(){
    start = std::chrono::system_clock::now();
}

int CountdownTimer::check() {
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);
    if (elapsed.count() > 0) {
        seconds_remaining -= elapsed.count();
        start = now;
    }
    return seconds_remaining;
}