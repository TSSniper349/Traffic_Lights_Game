#include"Car.h"

Car::Car(Coordination p_pos, short int road, short int p_lane, short int p_capacity, SDL_Texture* p_tex) {
    Enity::set_pos(p_pos);
    Enity::set_tex(p_tex);
    Enity::set_frame(20,40);
    Vehicle::set_speed(1);
    Vehicle::set_length(40);
    Vehicle::set_angle(road,p_lane);
    Vehicle::set_direction(road);
    Vehicle::set_capacity(p_capacity);
}