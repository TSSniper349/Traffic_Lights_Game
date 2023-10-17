#include"Road.h"

Road::Road() {
    list_of_lane = new Lane[3];
}

Road::Road(std::string pos) {
    list_of_lane = new Lane[3];
    if(pos == "Left") {
        *list_of_lane = Lane(Coordination(-25,405)); 
        *(list_of_lane+1) = Lane(Coordination(-25,430));
        *(list_of_lane+2) = Lane(Coordination(-25,455));
    }
    if(pos == "Right") {
        *list_of_lane = Lane(Coordination(960,555)); 
        *(list_of_lane+1) = Lane(Coordination(960,530));
        *(list_of_lane+2) = Lane(Coordination(960,505));
    }
    if(pos == "Top") {
        *list_of_lane = Lane(Coordination(555,-25)); 
        *(list_of_lane+1) = Lane(Coordination(530,-25));
        *(list_of_lane+2) = Lane(Coordination(505,-25));
    }
    if(pos == "Bottom") {
        *list_of_lane = Lane(Coordination(405,960)); 
        *(list_of_lane+1) = Lane(Coordination(430,960));
        *(list_of_lane+2) = Lane(Coordination(455,960));
    }

}

void Road::add_TrafficLight(TrafficLight* trafficlight){
    _trafficLight = trafficlight;
}

TrafficLight* Road::get_trafficlight(){
    return _trafficLight;
}   

Lane *Road::get_list_of_lane() {
    return list_of_lane;
}