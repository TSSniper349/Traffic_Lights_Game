#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include"Vehicle.h"

class Motorbike: public Vehicle {
    public:
    Motorbike() {};
    Motorbike(Coordination p_pos,short int road, short int p_lane, SDL_Texture* p_tex) {
        Enity::set_pos(p_pos);
        Enity::set_tex(p_tex);
        Enity::set_frame(20,25);
        Vehicle::set_speed(1.1);
        Vehicle::set_length(25);
        Vehicle::set_angle(road,p_lane);
        Vehicle::set_direction(road);
        Vehicle::set_capacity(2);

        through = false;
        have_add = false;
    }
};

#endif