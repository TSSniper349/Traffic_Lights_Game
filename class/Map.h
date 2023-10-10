#ifndef MAP
#define MAP

#include "Window.h"
using namespace std;

class Map{
    public:
        Map(int w, int h, int x, int y,const string &image_path);
    
        void draw() const;
        void pollEvents(SDL_Event $event);
        ~Map();
    
    private:
        int _w, _h;
        int _x, _y;
        SDL_Texture *_map_texture = nullptr;
};

#endif
