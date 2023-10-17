#pragma once
#include"Lane.h"
#include"TrafficLight.h"
#include<iostream>

// represent the roads
class Road {
    private:
        Lane *list_of_lane;// the list of the lanes
        std::string pos;// postion of the roads
        TrafficLight *_trafficLight;// traffic light objects of the roads
    public:
        Road();
        Road(std::string pos);

        void add_TrafficLight(TrafficLight *traffic_light);
        TrafficLight* get_trafficlight();
        Lane *get_list_of_lane();
        ~Road() {delete list_of_lane;}
};