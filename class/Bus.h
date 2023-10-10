#ifndef BUS
#define BUS

#include "Window.h"
using namespace std;

class Bus{
    public:
        Bus(int w, int h, int x, int y,const string &image_path);
    
        void draw() const;
        void move();
        void pollEvents(SDL_Event $event);
        ~Bus();
    
    private:
        int _w, _h;
        int _x, _y;
        SDL_Texture *_bus_texture = nullptr;
};

#endif
