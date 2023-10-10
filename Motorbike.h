#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include"NormalVehicle.h"

class Motorbike: public NormalVehicle {
    public:
    Motorbike(Coordination p_pos,short int road, short int p_lane, SDL_Texture* p_tex);
};

#endif