#pragma once
#include"Lane.h"
#include"TrafficLight.h"
#include<iostream>

class Road {
    private:
        Lane *list_of_lane;
        std::string pos;
        TrafficLight *_trafficLight;
    public:
        Road();
        Road(std::string pos);

        void add_TrafficLight(TrafficLight *traffic_light);
        TrafficLight* get_trafficlight();
        void pollEvents(SDL_Keycode keycode);

        Lane *get_list_of_lane();
};