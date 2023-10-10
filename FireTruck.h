#ifndef FIRETRUCK_H
#define FIRETRUCK_H

#include"SpecialVehicle.h"

class FireTruck: public SpecialVehicle {
    public:
    FireTruck(Coordination p_pos, short int capacity, SDL_Texture* p_tex);
    void turn();
};

#endif