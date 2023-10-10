#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "TrafficLight.h"
#include "Road.h"
#include <string>
#include <iostream>

using namespace std;

Road::Road() {
    _curr_size = 0;
}

void Road::add_TrafficLight(TrafficLight* trafficlight){
    _trafficlight = trafficlight;
    _curr_size++;
}

TrafficLight* Road::get_trafficlight(){
    return _trafficlight;
}   

void Road::pollEvents(SDL_Keycode keycode){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN){
            cout << event.key.keysym.sym << " " << keycode << endl;
            if (event.key.keysym.sym == keycode && _trafficlight->get_countdown_time() == 10) {
                _trafficlight->set_color("green");
            }
        }
    }
    
}

