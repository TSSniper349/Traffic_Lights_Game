#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <thread>

// represents the timer for the traffic lights
class CountdownTimer {
    public:

        CountdownTimer(int seconds);
        CountdownTimer();
        void set_time(int seconds);

        void Start();

        int check();

    private:
        int seconds_remaining;// the remaining seconds of the timer
        std::chrono::system_clock::time_point start;// the varible that stores current time of the system
};