#include"Vehicle.h"

// move the vehicle in the specified direction
void Vehicle::go() {
    if(direction == 0) {
        if(angle<90) angle+=0.01;
        else if(angle>90) angle-=0.01;
        pos_x+=0.1*speed;
    }
    if(direction == 1) {
        if(angle<10) angle +=360;
        if(angle<270) angle+=0.1;
        else if(angle>270) angle-=0.01;
        pos_x-=0.1*speed;
    }
    if(direction == 2) { 
        if(angle<180) angle+=0.01;
        else if(angle>180) angle-=0.01;
        pos_y+=0.1*speed;
    }
    if(direction == 3) {
        if(angle>350) angle-=360;
        if(angle<0) angle+=0.01;
        else if(angle>0) angle-=0.01;
        pos_y-=0.1*speed;
    }
}

// the vehicle turn left 
void Vehicle::turnLeft() {
    if(inLane==0) {
        pos_x+=0.06;
        pos_y-=0.06;
        angle-=0.15;
        if(angle>=-10&&angle<=10) direction = 3;
    }
    if(inLane==3) {
        pos_x-=0.06;
        pos_y+=0.06;
        angle-=0.15;
        if(angle>=170&&angle<=190) direction = 2;
    }
    if(inLane==6) {
        pos_x+=0.06;
        pos_y+=0.06;
        angle-=0.15;
        if(angle>=80&&angle<=100) direction = 0;
    }
    if(inLane==9) {
        pos_x-=0.06;
        pos_y-=0.06;
        angle-=0.15;
        if(angle<=-80&&angle>=-100) direction = 1;
    }
}

// the vehicle turn right
void Vehicle::turnRight() {
    if(inLane==2) {
        pos_x+=0.08;
        pos_y+=0.08;
        angle+=0.05;
        if(angle>=170&&angle<=190) direction = 2;
    }
    if(inLane==5) {
        pos_x-=0.08;
        pos_y-=0.08;
        angle+=0.05;
        if(angle>=350&&angle<=360) direction = 3;
    }
    if(inLane==8) {
        pos_x-=0.08;
        pos_y+=0.08;
        angle+=0.05;
        if(angle>=260&&angle<=280) direction = 1;
    }
    if(inLane==11) {
        pos_x+=0.08;
        pos_y-=0.08;
        angle+=0.05;
        if(angle>=80&&angle<=100) direction = 0;
    }
}

// set the angle for the rendering texture
void Vehicle::set_angle(short int road, short int p_lane) {
    inLane = road*3+p_lane;
    if(inLane<3) angle = 90;
    else if(inLane>=3 && inLane<6) angle = 270;
    else if(inLane>=6 && inLane<9) angle = 180;
    else angle = 0;
}

// set the state of the vehicle that it has exitted the intersection
void Vehicle::set_through(){
    through = true;
}

// return the state of the vehicle whether it has exitted the intersection
bool Vehicle::get_through(){
    return through;
}

// set the state of the vehicle that its length has been added to the current length of the lane
void Vehicle::set_have_add(){
    have_add = true;
}

// return the state of the vehicle whether it has been added to the current length of the lane
bool Vehicle::get_have_add(){
    return have_add;
}