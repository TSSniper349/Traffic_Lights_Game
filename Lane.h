#ifndef LANE_H
#define LANE_H

#include"Vehicle.h"
#include"Coordination.h"
#include<vector>

class Lane {
    private:
        float max_length;
        float curr_length;
        std::vector<Vehicle> *list_vehicles;
        Coordination pos;
    public:
    Lane();
    Lane(Coordination p_pos);
    float get_max_length();
    float get_curr_length();
    std::vector<Vehicle>* get_list_vehicles();

    Coordination get_pos();
    void addVehicle(Vehicle p_vehicle);
    void addLength(Vehicle p_vehicle);
    void vehicleThrough(std::vector<Vehicle>::iterator x);
    void delVehicle(std::vector<Vehicle>::iterator x);
    void clear_vehicle();
    ~Lane() {}
};

#endif