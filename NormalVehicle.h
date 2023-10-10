#pragma once
#include"Vehicle.h"

class NormalVehicle: public Vehicle {
    private:
        short int capacity;
    public:
    NormalVehicle() {};    
    void set_capacity(short int p_capacity);
    short int get_capacity() {return capacity;};
};
