#pragma once
#include"Vehicle.h"

class Car: public Vehicle {
    public:
    Car(Coordination p_pos, short int road, short int p_lane, short int capacity, SDL_Texture* p_tex);
    //~Car() {}
};