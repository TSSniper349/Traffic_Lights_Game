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
        Enity(Coordination p_pos, SDL_Texture* p_tex): pos(p_pos), tex(p_tex) {
            frame.x = 0;
            frame.y = 0;
            frame.w = 960;
            frame.h = 960;
        };
        Coordination &get_pos() {return pos;}
        SDL_Texture* get_tex() {return tex;}
        SDL_Rect get_frame() {return frame;}

        void set_pos(Coordination p_pos) {pos = p_pos;};
        void set_tex(SDL_Texture* p_tex) {tex = p_tex;};
        void set_frame(short int w, short int h) {
            frame.x = 0;
            frame.y = 0;
            frame.w = w;
            frame.h = h;
        };

        ~Enity() {};
};