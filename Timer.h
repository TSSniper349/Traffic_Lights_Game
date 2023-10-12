#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <thread>


class CountdownTimer {
    public:

        CountdownTimer(int seconds);
        CountdownTimer();
        void set_time(int seconds);

        void Start();

        int check();

    private:
        int seconds_remaining;
        std::chrono::system_clock::time_point start;
};