#ifndef VEHICLE_H
#define VEHICLE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Enity.h"

class Vehicle: public Enity {
    protected:
        short int direction;
        short int inLane;
        float length;
        float speed;
        short int score;
        SDL_Point center;
        float angle;
    public:
        Vehicle() {};
        short int get_direction() {return direction;};
        float get_length() {return length;};
        float get_speed() {return speed;};
        float get_score() {return score;};
        SDL_Point &get_center() {return center;};
        float get_angle() {return angle;};
        short int get_lane() {return inLane;};

        void set_length(float p_length) {length = p_length;};
        void set_center(float x, float y);
        void set_angle(short int road, short int p_lane);
        void set_direction(short int p_direction) {direction = p_direction;};
        void set_speed(float p_speed) {speed = p_speed;};

        void go();
        void stop();
        void turnLeft();
        void turnRight();
};

#endif
