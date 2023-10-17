#ifndef VEHICLE_H
#define VEHICLE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Enity.h"

// represent a vehicle and derive from the Entity class
class Vehicle: public Enity {
    protected:
        short int direction;// direction the vehicle will go
        short int inLane;// the lane that the vehicle is in
        short int capacity;// how many people are in the vehicle
        float length;// the length of the vehicle
        float speed;// the speed of the vehicle
        SDL_Point center;// the center of the vehicle texture
        float angle;// the angle of the vehicle texture
        bool through;// if the vehicle has exitted the intersection
        bool have_add;// whether the vehicle has been added to the current length of the lane
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
};

#endif
