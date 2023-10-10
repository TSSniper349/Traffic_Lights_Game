#include"Ambulance.h"

Ambulance::Ambulance(Coordination p_pos, short int p_capacity, SDL_Texture* p_tex) {
    Vehicle::set_pos(p_pos);
    Vehicle::set_tex(p_tex);
    Vehicle::set_frame(25,50);
    Vehicle::set_speed(5);
    Vehicle::set_length(10);
}

//Car::Car(SDL_Texture* p_tex): Car(Coordination(0,0),3,p_tex) {}

void Ambulance::turn() {

}