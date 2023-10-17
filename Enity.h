#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Coordination.h"

// represent entities in the game, derive from the Coordination Class
class Enity: public Coordination{
    protected:
        SDL_Rect frame;// the frame of the entity
        SDL_Texture* tex;// the texture of the entity
    public:
        Enity() {};
        // initialize default values for the coordination of the entity
        Enity(short int x, short int y, SDL_Texture* p_tex): tex(p_tex) {
            pos_x = x;
            pos_y = y;
            frame.x = 0;
            frame.y = 0;
            frame.w = 960;
            frame.h = 960;
        };
        //return the values of the entity
        float get_pos_x() {return pos_x;}
        float get_pos_y() {return pos_y;}
        SDL_Texture* get_tex() {return tex;}
        SDL_Rect get_frame() {return frame;}

        // set the neccessary values for the entity
        void set_pos_x(float p_x) {pos_x = p_x;}
        void set_pos_y(float p_y) {pos_y = p_y;}
        void set_tex(SDL_Texture* p_tex) {tex = p_tex;};
        void set_frame(short int w, short int h) {
            frame.x = 0;
            frame.y = 0;
            frame.w = w;
            frame.h = h;
        };

        ~Enity() {}
};