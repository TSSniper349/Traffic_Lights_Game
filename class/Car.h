#ifndef CAR
#define CAR

#include "Window.h"
using namespace std;

class Car{
    public:
        Car(int w, int h, int x, int y,const string &image_path);
    
        void draw() const;
        void move();
        void pollEvents(SDL_Event $event);
        ~Car();
    
    private:
        int _w, _h;
        int _x, _y;
        SDL_Texture *_car_texture = nullptr;
};

#endif
