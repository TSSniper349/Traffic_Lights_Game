#pragma once
#include"Lane.h"
#include<iostream>

class Road {
    private:
        Lane *list_of_lane;
        std::string pos;
        //traffic_light here
    public:
        Road();
        Road(std::string pos);

        Lane *get_list_of_lane();
};