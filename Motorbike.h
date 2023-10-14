#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include"Vehicle.h"

class Motorbike: public Vehicle {
    public:
    Motorbike(Coordination p_pos,short int road, short int p_lane, SDL_Texture* p_tex);
};

#endif