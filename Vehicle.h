#ifndef VEHICLE_H
#define VEHICLE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Enity.h"

class Vehicle: public Enity {
    protected:
        short int direction;
        short int inLane;
        short int capacity;
        float length;
        float speed;
        SDL_Point center;
        float angle;
        bool through;
        bool have_add;
    public:
        Vehicle() {};
        short int get_direction() {return direction;};
        float get_length() {return length;};
        float get_speed() {return speed;};
        float get_angle() {return angle;};
        short int get_lane() {return inLane;};
        short int get_capacity() {return capacity;};
        SDL_Point &get_center() {return center;};
        bool get_through();
        bool get_have_add();

        void set_length(float p_length) {length = p_length;};
        void set_angle(short int road, short int p_lane);
        void set_direction(short int p_direction) {direction = p_direction;};
        void set_speed(float p_speed) {speed = p_speed;};
        void set_capacity(short int p_capaciy) {capacity = p_capaciy;};
        void set_through();
        void set_have_add();

        void go();
        void turnLeft();
        void turnRight();
        //~Vehicle() {};
};

#endif
