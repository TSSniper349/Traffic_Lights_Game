#ifndef VEHICLE_H
#define VEHICLE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Coordination.h"

class Vehicle {
    protected:
        short int direction;
        float length;
        float speed;
        short int score;
        Coordination pos;
        SDL_Rect frame;
        SDL_Texture* tex;
    public:
        short int get_direction();
        float get_length();
        float get_speed();
        float get_score();
        Coordination &get_pos();
        SDL_Texture* get_tex();
        SDL_Rect get_frame();

        void set_pos(Coordination p_pos);
        void set_tex(SDL_Texture* p_tex);
        void set_frame(short int w, short int h);
        void set_length(float p_length);

        void go(short int dir);
        void stop();
        void set_speed(float p_speed);
        //virtual void turn() = 0;
        //~Vehicle();
};

#endif
