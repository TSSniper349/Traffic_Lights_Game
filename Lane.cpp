#include"Lane.h"
#include<iostream>

Lane::Lane(): Lane(0,0) {}

Lane::Lane(float x, float y) {
    list_vehicles = new std::vector<Vehicle>;
    max_length = 375;
    pos_x = x;
    pos_y = y;
    curr_length = 0;
}

std::vector<Vehicle>* Lane::get_list_vehicles() {
    return list_vehicles;
}

void Lane::addVehicle(Vehicle p_vehicle) {
    list_vehicles->push_back(p_vehicle);
}

void Lane::addLength(Vehicle p_vehicle){
    curr_length += p_vehicle.get_length() + 6;
}

void Lane::vehicleThrough(std::vector<Vehicle>::iterator x) {
    curr_length -= x->get_length() - 6;
}

void Lane::delVehicle(std::vector<Vehicle>::iterator x) {
    list_vehicles->erase(x);
}

void Lane::clear_vehicle(){
    list_vehicles->clear();
    curr_length = 0;
}

