#ifndef ROAD
#define ROAD
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "TrafficLight.h"
#include <string>

using namespace std;

class Road{
    private:
        int _curr_size;
        int _size;
        TrafficLight *_trafficlight;
    public:
        Road();
        void add_TrafficLight(TrafficLight* trafficlight);
        TrafficLight* get_trafficlight();
        void pollEvents(SDL_Keycode keycode);
};

#endif