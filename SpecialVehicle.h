#ifndef SPECIALVEHICLE_H
#define SPECIALVEHILCE_H

#include"Vehicle.h"

class SpecialVehicle: public Vehicle {
    private:
        short int waiting_time;
        bool siren;
    public:
        short int get_waiting_time();
};

#endif