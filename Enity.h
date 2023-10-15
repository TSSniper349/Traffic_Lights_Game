#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Coordination.h"

class Enity {
    protected:
        Coordination pos;
        SDL_Rect frame;
        SDL_Texture* tex;
    public:
        Enity() {};
        Enity(Coordination p_pos, SDL_Texture* p_text);
        Coordination &get_pos();
        SDL_Texture* get_tex();
        SDL_Rect get_frame();

        void set_pos(Coordination p_pos) {pos = p_pos;};
        void set_tex(SDL_Texture* p_tex) {tex = p_tex;};
        void set_frame(short int w, short int h);

        ~Enity();
};