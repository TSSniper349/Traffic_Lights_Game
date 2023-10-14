#pragma once
#include"Vehicle.h"

class Bus: public Vehicle {
    public:
    Bus(Coordination p_pos,short int road, short int p_lane, short int capacity, SDL_Texture* p_tex);
};