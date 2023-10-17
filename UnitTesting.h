#ifndef UNITTEST
#define UNITTEST
#include <string>
#include "Lane.h"
#include "Utils.h"
#include "Text.h"
#include <vector>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include "RenderWindow.h"
#include "car.h"
#include "Bus.h"
#include "Motorbike.h"
#include "Enity.h"
#include "Road.h"
#include<stdio.h>
using namespace std;


class UnitTest{
    public:
        void runTests(){
            TestTimer();
            TestCoordinate();
            TestEnity();
            TestTrafficLight();
            TestVehicle();
            TestCar();
            TestBus();
            TestMotorbike();
            TestLane();
            TestRoad();
        }
    private:
        void TestTimer(){
            CountdownTimer timer(20);

            timer.Start();
            int t = timer.check();
            if (t != 20){
                cout << "Timer-Test 1 failed" << " " << t << endl;
            }
            timer.set_time(18);
            timer.Start();
            t = timer.check();
            if (t != 18){
                cout << "Timer-Test 2 failed" << " " << t << endl;
            }
        }
        void TestTrafficLight(){
            TrafficLight *trafficlightLeft = new TrafficLight(nullptr, 340, 320, "res/gfx/red.png", 6); 

            if (trafficlightLeft->get_curr_color() != "red"){
                cout << "TrafficLight-Test 1 failed" << endl;
            }
            if (trafficlightLeft->get_frame().w != 33 || trafficlightLeft->get_frame().h != 88){
                cout << "TrafficLight-Test 2 failed" << endl;
            }
            if (trafficlightLeft->get_pos_x() != 340 || trafficlightLeft->get_pos_y() != 320){
                cout << "TrafficLight-Test 3 failed" << endl;
            }
            if (trafficlightLeft->get_timer() != 6){
                cout << "TrafficLight-Test 4 failed" << endl;
            }
            trafficlightLeft->set_color("yellow");
            if (trafficlightLeft->get_curr_color() != "yellow"){
                cout << "TrafficLight-Test 5 failed" << endl;
            }
            trafficlightLeft->set_countdowntime(20);
            if (trafficlightLeft->get_countdown_time() != 20){
                cout << "TrafficLight-Test 6 failed" << endl;
            }
            trafficlightLeft->ChangeColor(nullptr, "res/gfx/green.png", "green");
            if (trafficlightLeft->get_curr_color() != "green"){
                cout << "TrafficLight-Test 7 failed" << endl;
            }
            delete trafficlightLeft;
        }
        void TestMotorbike(){
            Vehicle *motorbike = new Motorbike(1,1, 1, 1, nullptr);

            if (motorbike->get_frame().w != 20 || motorbike->get_frame().h != 25){
                cout << "Motorbike-Test 1 failed" << endl;
            }
            if (motorbike->get_pos_x() != 1 || motorbike->get_pos_y() != 1){
                cout << "Motorbike-Test 2 failed" << endl;
            }
            if (motorbike->get_tex() != nullptr){
                cout << "Motorbike-Test 3 failed" << endl;
            }
            if (motorbike->get_speed() != (float)1.1){
                cout << "Motorbike-Test 4 failed" << endl;
            }
            if (motorbike->get_length() != 25){
                cout << "Motorbike-Test 5 failed" << endl;
            }
            if (motorbike->get_direction() != 1){
                cout << "Motorbike-Test 6 failed" << endl;
            }

            if (motorbike->get_angle() != 270){
                cout << "Motorbike-Test 7 failed" << endl;
            }
            delete motorbike;
        }
        void TestBus(){
            Vehicle *bus = new Bus(1,1, 1, 1, 2, nullptr);

            if (bus->get_frame().w != 20 || bus->get_frame().h != 75){
                cout << "Bus-Test 1 failed" << endl;
            }
            if (bus->get_pos_x() != 1 || bus->get_pos_y() != 1){
                cout << "Bus-Test 2 failed" << endl;
            }
            if (bus->get_tex() != nullptr){
                cout << "Bus-Test 3 failed" << endl;
            }
            if (bus->get_speed() != (float)0.9){
                cout << "Bus-Test 4 failed" << endl;
            }
            if (bus->get_length() != 75){
                cout << "Bus-Test 5 failed" << endl;
            }
            if (bus->get_capacity() != 2){
                cout << "Bus-Test 6 failed" << endl;
            }
            if (bus->get_direction() != 1){
                cout << "Bus-Test 7 failed" << endl;
            }

            if (bus->get_angle() != 270){
                cout << "Bus-Test 8 failed" << endl;
            }
            delete bus;
        }
        void TestCar(){
            Vehicle *car = new Car(1,1, 1, 1, 2, nullptr);

            if (car->get_frame().w != 20 || car->get_frame().h != 40){
                cout << "Car-Test 1 failed" << endl;
            }
            if (car->get_pos_x() != 1 || car->get_pos_y() != 1){
                cout << "Car-Test 2 failed" << endl;
            }
            if (car->get_tex() != nullptr){
                cout << "Car-Test 3 failed" << endl;
            }
            if (car->get_speed() != 1){
                cout << "Car-Test 4 failed" << endl;
            }
            if (car->get_length() != 40){
                cout << "Car-Test 5 failed" << endl;
            }
            if (car->get_capacity() != 2){
                cout << "Car-Test 6 failed" << endl;
            }
            if (car->get_direction() != 1){
                cout << "Car-Test 7 failed" << endl;
            }

            if (car->get_angle() != 270){
                cout << "Car-Test 8 failed" << endl;
            }
            delete car;
        }
        void TestVehicle(){
            Vehicle bus;
            bus.set_length(20);
            if (bus.get_length() != 20){
                cout << "Vehicle-Test 1 failed" << endl;
            }

            bus.set_angle(2,3);
            if (bus.get_angle() != 0){
                cout << "Vehicle-Test 2 failed" << endl;
            }

            bus.set_direction(1);
            if (bus.get_direction() != 1){
                cout << "Vehicle-Test 3 failed" << endl;
            }

            bus.set_speed(10);
            if (bus.get_speed() != 10){
                cout << "Vehicle-Test 4 failed" << endl;
            }

            bus.set_capacity(12);
            if(bus.get_capacity() != 12){
                cout << "Vehicle-Test 5 failed" << endl;
            }

            bus.set_through();
            if(bus.get_through() != true){
                cout << "Vehicle-Test 6 failed" << endl;
            }

            bus.set_have_add();
            if(bus.get_have_add() != true){
                cout << "Vehicle-Test 7 failed" << endl;
            }

            Vehicle *car = new Car();

            car->go();
            if (car->get_pos_x() != (float)0.1){
                cout << "Vehicle-Test 8 failed" << " " << car->get_pos_x() <<  endl;
            }

            car->turnLeft();
            if (car->get_pos_x() != (float)0.16 || car->get_pos_y() != (float)(-0.06) || car->get_angle() != (float)(89.85)){
                cout << "Vehicle-Test 9 failed" << endl;
            }

            car->set_pos_x(0);
            car->set_pos_y(0);
            car->set_angle(0,2);
            car->turnRight();
            if (car->get_pos_x() != (float)0.08 || car->get_pos_y() != (float)0.08 || car->get_angle() != (float)90.05){
                cout << "Vehicle-Test 10 failed " <<  car->get_angle() << endl;
            }

            delete car;
            
        }
        void TestEnity(){
            Enity Object;

            Object.set_pos_x(1);
            Object.set_pos_y(2);
            if (Object.get_pos_x() != 1 || Object.get_pos_y()  != 2){
                cout << "Enity-Test 1 failed" << endl;
            }

            Object.set_frame(10, 20);
            SDL_Rect frame = Object.get_frame();
            if (frame.w != 10 || frame.h != 20){
                cout << "Enity-Test 2 failed" << endl;
            }

            Object.set_tex(nullptr);
            if (Object.get_tex() != nullptr){
                cout << "Enity-Test 3 failed" << endl;
            }

            Enity Background(10, 20, nullptr);
            if (Background.get_pos_x() != 10 || Background.get_pos_y() != 20){
                cout << "Enity-Test 4 failed" << endl;
            }
            if (Background.get_tex() != nullptr){
                cout << "Enity-Test 5 failed" << endl;
            }
            if (Background.get_frame().w != 960 || Background.get_frame().h != 960){
                cout << "Enity-Test 6 failed" << endl;
            }


        }
        void TestLane(){
            Lane lane;
            if (lane.get_max_length() != 375){
                cout << "Lane-Test 1 failed" << endl;
            }
            if (lane.get_curr_length() != 0 || lane.get_pos_x() != 0 || lane.get_pos_y() != 0){
                cout << "Lane-Test 2 failed" << endl;
            }
            
            Car car;
            lane.addVehicle(car);
            Bus bus;
            lane.addVehicle(bus);

            std::vector<Vehicle> *vehicles_list = lane.get_list_vehicles();

            std::vector<Vehicle>::iterator x = vehicles_list->begin();

            if (x->get_length() != car.get_length()){
                cout << "Lane-Test 3 failed" << endl;
            }

            if ((x+1)->get_length() != bus.get_length()){
                cout << "Lane-Test 4 failed" << endl;
            }
            
            lane.addLength(car);
            if (lane.get_curr_length() != car.get_length() + 6){
                cout << "Lane-Test 5 failed" << endl;
            }

            lane.vehicleThrough(x);
            lane.delVehicle(x);
            lane.addLength(bus);

            if (lane.get_curr_length() != bus.get_length() + 6){
                cout << "Lane-Test 6 failed" << " " << lane.get_curr_length() << endl;
            }

            lane.clear_vehicle();
            std::vector<Vehicle> *vehicles_list_cleared = lane.get_list_vehicles();
            if (vehicles_list_cleared->size() != 0){
                cout << "Lane-Test 7 failed" << endl;
            }
            if (lane.get_curr_length() != 0) {
                cout << "Lane-Test 8 failed" << endl;
            }           
        }
        void TestCoordinate(){
            Lane lane;
            
            lane.set_pos_x(6.12);
            lane.set_pos_y(19.5);

            if (lane.get_pos_x() != (float)6.12 || lane.get_pos_y() != (float)19.5){
                cout << "Coordinate-Test 1 failed" << endl;
            }
            
            Vehicle vehicle;

            vehicle.set_pos_x(19.5);
            vehicle.set_pos_y(6.12);

            if (vehicle.get_pos_x() != (float)19.5 || vehicle.get_pos_y() != (float)6.12){
                cout << "Coordiante-Test 2 failed" << endl;
            }
        }
        void TestRoad(){
            Road road1("Left");
            for (short int i = 0; i < 3; i++){
                Lane *tmp = road1.get_list_of_lane() + i;
                if (i == 0){
                    if (tmp->get_pos_x() != Lane(-25,405).get_pos_x() || tmp->get_pos_y() != Lane(-25,405).get_pos_y()){
                        cout << "Road-Test 1 failed" << " " << tmp->get_pos_y() << endl;
                    }
                }
                else if (i == 1) {
                    if (tmp->get_pos_x() != Lane(-25,430).get_pos_x() || tmp->get_pos_y() != Lane(-25,430).get_pos_y()){
                        cout << "Road-Test 2 failed" << endl;
                    }
                }
                else {
                    if (tmp->get_pos_x() != Lane(-25,455).get_pos_x() || tmp->get_pos_y() != Lane(-25,455).get_pos_y()){
                        cout << "Road-Test 3 failed" << endl;
                    }
                }
            }
            SDL_Renderer *render = nullptr;
            TrafficLight *trafficlightLeft = new TrafficLight(render, 340, 320, "res/gfx/red.png", 6);
            road1.add_TrafficLight(trafficlightLeft);

            if (road1.get_trafficlight()->get_pos_x() != trafficlightLeft->get_pos_x() || road1.get_trafficlight()->get_pos_y() != trafficlightLeft->get_pos_y()){
                cout << "Road-Test 4 failed";
            }     

            delete trafficlightLeft;       
        }

};


#endif
