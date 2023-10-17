#include <iostream>
#include "Timer.h"

// initialize timer with specified value
CountdownTimer::CountdownTimer(int seconds) : seconds_remaining(seconds) {
        }

// initialize the timer with 0 second
CountdownTimer::CountdownTimer() : CountdownTimer(0){}

//change the time of the countdown timer
void CountdownTimer::set_time(int seconds){
            seconds_remaining = seconds;

}

// start the timer by storing current time in the start variable
void CountdownTimer::Start(){
    start = std::chrono::system_clock::now();
}

// return the remaining seconds of the timer
int CountdownTimer::check() {
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);
    if (elapsed.count() > 0) {
        seconds_remaining -= elapsed.count();
        start = now;
    }
    return seconds_remaining;
}