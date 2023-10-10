#ifndef POLICECAR_H
#define POLICECAR_H

#include"SpecialVehicle.h"

class PoliceCar: public SpecialVehicle {
    public:
    PoliceCar(Coordination p_pos, short int capacity, SDL_Texture* p_tex);
    void turn();
};

#endif