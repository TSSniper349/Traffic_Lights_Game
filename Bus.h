#pragma once
#include"Vehicle.h"

class Bus: public Vehicle {
    public:
    Bus() {};
    Bus(float x, float y,short int road, short int p_lane, short int capacity, SDL_Texture* p_tex) {
        Enity::set_pos_x(x);
        Enity::set_pos_y(y);
        Enity::set_tex(p_tex);
        Enity::set_frame(20,75);
        Vehicle::set_speed(0.9);
        Vehicle::set_length(75);
        Vehicle::set_angle(road,p_lane);
        Vehicle::set_direction(road);
        Vehicle::set_capacity(capacity);

        through = false;
        have_add = false;
    }
};