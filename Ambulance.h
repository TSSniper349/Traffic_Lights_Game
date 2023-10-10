#ifndef AMBULANCE_H
#define AMBULANCE_H

#include"SpecialVehicle.h"

class Ambulance: public SpecialVehicle {
    public:
    Ambulance(Coordination p_pos, short int capacity, SDL_Texture* p_tex);
    void turn();
};

#endif

