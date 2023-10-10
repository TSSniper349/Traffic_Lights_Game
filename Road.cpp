#include"Road.h"

Road::Road() {
    list_of_lane = new Lane[3];
}

Road::Road(std::string pos) {
    list_of_lane = new Lane[3];
    if(pos == "Left") {
        *list_of_lane = Lane(Coordination(-25,395)); 
        *(list_of_lane+1) = Lane(Coordination(-25,420));
        *(list_of_lane+2) = Lane(Coordination(-25,445));
    }
    if(pos == "Right") {
        *list_of_lane = Lane(Coordination(960,525)); 
        *(list_of_lane+1) = Lane(Coordination(960,500));
        *(list_of_lane+2) = Lane(Coordination(960,475));
    }
    if(pos == "Top") {
        *list_of_lane = Lane(Coordination(535,-25)); 
        *(list_of_lane+1) = Lane(Coordination(510,-25));
        *(list_of_lane+2) = Lane(Coordination(485,-25));
    }
    if(pos == "Bottom") {
        *list_of_lane = Lane(Coordination(405,960)); 
        *(list_of_lane+1) = Lane(Coordination(430,960));
        *(list_of_lane+2) = Lane(Coordination(455,960));
    }

}

Lane *Road::get_list_of_lane() {
    return list_of_lane;
}