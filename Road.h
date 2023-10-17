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
        Lane *get_list_of_lane();
        ~Road() {delete list_of_lane;}
};