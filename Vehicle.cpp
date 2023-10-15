#include"Vehicle.h"

void Vehicle::go() {
    if(direction == 0) {
        if(angle<90) angle+=0.01;
        else if(angle>90) angle-=0.01;
        pos.x+=0.1*speed;
    }
    if(direction == 1) {
        if(angle<10) angle +=360;
        if(angle<270) angle+=0.1;
        else if(angle>270) angle-=0.01;
        pos.x-=0.1*speed;
    }
    if(direction == 2) { 
        if(angle<180) angle+=0.01;
        else if(angle>180) angle-=0.01;
        pos.y+=0.1*speed;
    }
    if(direction == 3) {
        if(angle>350) angle-=360;
        if(angle<0) angle+=0.01;
        else if(angle>0) angle-=0.01;
        pos.y-=0.1*speed;
    }
}

void Vehicle::turnLeft() {
    if(inLane==0) {
        pos.x+=0.06;
        pos.y-=0.06;
        angle-=0.15;
        if(angle>=-10&&angle<=10) direction = 3;
    }
    if(inLane==3) {
        pos.x-=0.06;
        pos.y+=0.06;
        angle-=0.15;
        if(angle>=170&&angle<=190) direction = 2;
    }
    if(inLane==6) {
        pos.x+=0.06;
        pos.y+=0.06;
        angle-=0.15;
        if(angle>=80&&angle<=100) direction = 0;
    }
    if(inLane==9) {
        pos.x-=0.06;
        pos.y-=0.06;
        angle-=0.15;
        if(angle<=-80&&angle>=-100) direction = 1;
    }
}

void Vehicle::turnRight() {
    if(inLane==2) {
        pos.x+=0.08;
        pos.y+=0.08;
        angle+=0.05;
        if(angle>=170&&angle<=190) direction = 2;
    }
    if(inLane==5) {
        pos.x-=0.08;
        pos.y-=0.08;
        angle+=0.05;
        if(angle>=350&&angle<=360) direction = 3;
    }
    if(inLane==8) {
        pos.x-=0.08;
        pos.y+=0.08;
        angle+=0.05;
        if(angle>=260&&angle<=280) direction = 1;
    }
    if(inLane==11) {
        pos.x+=0.08;
        pos.y-=0.08;
        angle+=0.05;
        if(angle>=80&&angle<=100) direction = 0;
    }
}

void Vehicle::set_angle(short int road, short int p_lane) {
    inLane = road*3+p_lane;
    if(inLane<3) angle = 90;
    else if(inLane>=3 && inLane<6) angle = 270;
    else if(inLane>=6 && inLane<9) angle = 180;
    else angle = 0;
}

void Vehicle::set_through(){
    through = true;
}

bool Vehicle::get_through(){
    return through;
}

void Vehicle::set_have_add(){
    have_add = true;
}

bool Vehicle::get_have_add(){
    return have_add;
}