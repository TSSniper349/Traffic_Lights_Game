#include"Lane.h"
#include<iostream>

// initialize lane's coordination to (0,0)
Lane::Lane(): Lane(0,0) {}

// create a new list of vehicles and set the neccessary values
Lane::Lane(float x, float y) {
    list_vehicles = new std::vector<Vehicle>;
    max_length = 375;
    pos_x = x;
    pos_y = y;
    curr_length = 0;
}

// return the pointer to the list of vehicles
std::vector<Vehicle>* Lane::get_list_vehicles() {
    return list_vehicles;
}

// add new vehicle to the list
void Lane::addVehicle(Vehicle p_vehicle) {
    list_vehicles->push_back(p_vehicle);
}

// add length of the vehicle to current length of the lane
void Lane::addLength(Vehicle p_vehicle){
    curr_length += p_vehicle.get_length() + 6;
}

// take length of the vehicle from current length of the lane when it is out of the intersection
void Lane::vehicleThrough(std::vector<Vehicle>::iterator x) {
    if (curr_length - x->get_length() - 6 >= 0) curr_length = curr_length - x->get_length() - 6;
}

// delete the vehicle after exitting the screen
void Lane::delVehicle(std::vector<Vehicle>::iterator x) {
    list_vehicles->erase(x);
}

// delete the list of vehicles after the game ends
void Lane::clear_vehicle(){
    list_vehicles->clear();
    curr_length = 0;
}

