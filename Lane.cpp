#include"Lane.h"
#include<iostream>

Lane::Lane(): Lane(Coordination(0,0)) {}

Lane::Lane(Coordination p_pos) {
    list_vehicles = new std::vector<Vehicle>;
    max_length = 400;
    pos = p_pos;
    curr_length = 0;
}

float Lane::get_max_length() {
    return max_length;
}

float Lane::get_curr_length() {
    return curr_length;
}

Coordination Lane::get_pos() {
    return pos;
}

std::vector<Vehicle>* Lane::get_list_vehicles() {
    return list_vehicles;
}

void Lane::addVehicle(Vehicle p_vehicle) {
    list_vehicles->push_back(p_vehicle);
    curr_length += p_vehicle.get_length();
}

void Lane::vehicleThrough(std::vector<Vehicle>::iterator x) {
    curr_length -= x->get_length();
}

void Lane::delVehicle(std::vector<Vehicle>::iterator x) {
    list_vehicles->erase(x);
}