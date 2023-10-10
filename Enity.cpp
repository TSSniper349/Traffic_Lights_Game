#include"Enity.h"

Enity::Enity(Coordination p_pos, SDL_Texture* p_tex): pos(p_pos), tex(p_tex) {
    frame.x = 0;
    frame.y = 0;
    frame.w = 960;
    frame.h = 960;
}

Coordination &Enity::get_pos() {
    return pos;
}

SDL_Texture* Enity::get_tex() {
    return tex;
}

SDL_Rect Enity::get_frame() {
    return frame;
}

void Enity::set_frame(short int w, short int h) {
    frame.x = 0;
    frame.y = 0;
    frame.w = w;
    frame.h = h;
}