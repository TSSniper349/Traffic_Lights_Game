#include"Bus.h"

Bus::Bus(Coordination p_pos, short int road, short int p_lane, short int p_capacity, SDL_Texture* p_tex) {
    Vehicle::set_pos(p_pos);
    Vehicle::set_tex(p_tex);
    Vehicle::set_frame(20,75);
    Vehicle::set_speed(0.9);
    Vehicle::set_length(75);
    Vehicle::set_center(0,0);
    Vehicle::set_angle(road,p_lane);
    Vehicle::set_direction(road);
    Vehicle::set_capacity(p_capacity);
}