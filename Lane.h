#ifndef LANE_H
#define LANE_H

#include"Vehicle.h"
#include"Coordination.h"
#include<vector>

class Lane: public Coordination {
    private:
        float max_length;
        float curr_length;
        std::vector<Vehicle> *list_vehicles;
    public:
    Lane();
    Lane(float x, float y);
    float get_max_length() {return max_length;}
    float get_curr_length() {return curr_length;}
    std::vector<Vehicle>* get_list_vehicles();
    float get_pos_x() {return pos_x;}
    float get_pos_y() {return pos_y;}

    void set_pos_x(float p_x) {pos_x = p_x;}
    void set_pos_y(float p_y) {pos_y = p_y;}
    void addVehicle(Vehicle p_vehicle);
    void addLength(Vehicle p_vehicle);
    void vehicleThrough(std::vector<Vehicle>::iterator x);
    void delVehicle(std::vector<Vehicle>::iterator x);
    void clear_vehicle();
    ~Lane() {}
};

#endif