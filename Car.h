#pragma once
#include"NormalVehicle.h"

class Car: public NormalVehicle {
    public:
    Car(Coordination p_pos, short int road, short int p_lane, short int capacity, SDL_Texture* p_tex);
};