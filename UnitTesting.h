#include"Car.h"
#include"Bus.h"
#include"Motorbike.h"
#include<iostream>
using namespace std;
//#include"TrafficLight.h"

class UnitTesting {
    private:
        Car *car = nullptr;
        Bus *bus = nullptr;
        Motorbike *motor = nullptr;
        //TrafficLight trafficLight;
        SDL_Texture *carTex;
        SDL_Texture *busTex;
        SDL_Texture *motorTex;
        //SDL_Texture *lightTex;
    public:
    UnitTesting() {
        car = new Car(Coordination(100,10),1,2,4,carTex);
        bus = new Bus(Coordination(250,250),0,0,1,carTex);
        motor = new Motorbike(Coordination(0,0),0,1,motorTex);
    };

    void testCar() {
        if(car==nullptr) {
            cout<<"Cannot Initiate Car"<<endl;
        }
        if(car->get_pos().x!=100||car->get_pos().y!=10) {
            cout<<"Car position wrong"<<endl;
        }
        if(car->get_lane()!=5) {
            cout<<"Car lane wrong"<<endl;
        }
        if(car->get_capacity()!=4) {
            cout<<"Car capacity wrong"<<endl;
        }
        if(car->get_angle()!=270) {
            cout<<"Car angle wrong"<<endl;
        }
        if(car->get_center().x!=0||car->get_center().y!=0) {
            cout<<"Car center wrong"<<endl;
        }
        if(car->get_frame().w!=20||car->get_frame().h!=40) {
            cout<<"Car frame wrong"<<endl;
        }
        if(car->get_direction()!=1) {
            cout<<"Car direction wrong"<<endl;
        }
        if(car->get_length()!=40) {
            cout<<"Car length wrong"<<endl;
        }
        if(car->get_speed()!=1) {
            cout<<"Car speed wrong"<<endl;
        }
    }
    void testBus() {
        if(bus==nullptr) {
            cout<<"Cannot Initiate Bus"<<endl;
        }
        if(bus->get_pos().x!=100||bus->get_pos().y!=10) {
            cout<<"Bus position wrong"<<endl;
        }
        if(bus->get_lane()!=5) {
            cout<<"Bus lane wrong"<<endl;
        }
        if(bus->get_capacity()!=4) {
            cout<<"Bus capacity wrong"<<endl;
        }
        if(bus->get_angle()!=270) {
            cout<<"Bus angle wrong"<<endl;
        }
        if(bus->get_center().x!=0||bus->get_center().y!=0) {
            cout<<"Bus center wrong"<<endl;
        }
        if(bus->get_frame().w!=20||bus->get_frame().h!=40) {
            cout<<"Bus frame wrong"<<endl;
        }
        if(bus->get_direction()!=1) {
            cout<<"Bus direction wrong"<<endl;
        }
        if(bus->get_length()!=40) {
            cout<<"Bus length wrong"<<endl;
        }
        if(bus->get_speed()!=1) {
            cout<<"Bus speed wrong"<<endl;
        }
    }
    void testMotor() {
        if(motor==nullptr) {
            cout<<"Cannot Initiate Motor"<<endl;
        }
        if(motor->get_pos().x!=100||motor->get_pos().y!=10) {
            cout<<"Motor position wrong"<<endl;
        }
        if(motor->get_lane()!=5) {
            cout<<"Motor lane wrong"<<endl;
        }
        if(motor->get_capacity()!=4) {
            cout<<"Motor capacity wrong"<<endl;
        }
        if(motor->get_angle()!=270) {
            cout<<"Motor angle wrong"<<endl;
        }
        if(motor->get_center().x!=0||motor->get_center().y!=0) {
            cout<<"Motor center wrong"<<endl;
        }
        if(motor->get_frame().w!=20||motor->get_frame().h!=40) {
            cout<<"Motor frame wrong"<<endl;
        }
        if(motor->get_direction()!=1) {
            cout<<"Motor direction wrong"<<endl;
        }
        if(motor->get_length()!=40) {
            cout<<"Motor length wrong"<<endl;
        }
        if(motor->get_speed()!=1) {
            cout<<"Motor speed wrong"<<endl;
        }
    }
};