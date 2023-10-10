#ifndef BUS_H
#define BUS_H

#include"NormalVehicle.h"

class Bus: public NormalVehicle {
    public:
    Bus(Coordination p_pos,short int road, short int p_lane, short int capacity, SDL_Texture* p_tex);
};

#endif