#include <iostream>
#include "class/Window.h"
#include "class/Map.h"
#include "class/Bus.h"
#include "class/Car.h"
#include "class/TrafficLight.h"
#include "class/Text.h"
#include "class/Road.h"
#include <SDL2/SDL.h>
#include <thread>
using namespace std;
const int WIDTH = 800, HEIGHT = 600;




int main( int argc, char *argv[] )
{
    Window window("Traffic light game", 800, 600);
    Map map(WIDTH, HEIGHT, 1, 1, "src/images/intersection.png");
    Car car(40, 20, 40, 20, "src/images/right/car.png");
    Bus bus(40, 20, 40, 50, "src/images/right/bus.png");
    TrafficLight* trafficlight1 = new TrafficLight(40, 50, 40, 90, "src/images/signals/red.png", 10);
    TrafficLight* trafficlight2 = new TrafficLight(40, 50, 150, 90, "src/images/signals/red.png", 10);
    TrafficLight* trafficlight3 = new TrafficLight(40, 50, 250, 90, "src/images/signals/red.png", 10);
    TrafficLight* trafficlight4 = new TrafficLight(40, 50, 350, 90, "src/images/signals/red.png", 10);
    Text text(Window::renderer, "hello");
    Road road1;
    Road road2;
    Road road3;
    Road road4;

    road1.add_TrafficLight(trafficlight1);   
    road2.add_TrafficLight(trafficlight2);
    road3.add_TrafficLight(trafficlight3);
    road4.add_TrafficLight(trafficlight4);

    TrafficLight* *TrafficLight_list;

    TrafficLight_list[0] = road1.get_trafficlight();
    TrafficLight_list[1] = road2.get_trafficlight();
    TrafficLight_list[2] = road3.get_trafficlight();
    TrafficLight_list[3] = road4.get_trafficlight();

    int check = 0;
    //CountdownTimer timer(10);
    int _curr_time[4] = {20, 10, 10 ,10};
    string tmp = "";

    while(!window.isClosed()){
        map.draw();
        car.draw();
        car.move();
        bus.draw();
        bus.move();
        for (short int i = 0; i < 4; i++){
            TrafficLight_list[i]->draw();
        }

        for (short int i = 0; i < 4; i++){
            Coor coor = TrafficLight_list[i]->get_coor();
            //cout << _curr_time[0] << " " << 0 << endl;
            if (TrafficLight_list[i]->get_curr_color() == "green"){
                if (_curr_time[i] == 10) TrafficLight_list[i]->ChangeColor("src/images/signals/green.png", "green");

                _curr_time[i] = TrafficLight_list[i]->get_timer();
                TrafficLight_list[i]->set_countdowntime(_curr_time[i]);
                tmp = to_string(_curr_time[i]);
                text.display(coor.x - 20,coor.y, Window::renderer, tmp.c_str());
                //cout << _curr_time << " seconds remaining" << endl;

                if (_curr_time[i] == 0) {
                    TrafficLight_list[i]->set_color("yellow");
                    TrafficLight_list[i]->set_countdowntime(5);
                    TrafficLight_list[i]->set_timer(5);
                    _curr_time[i] = 5;
                    tmp = to_string(_curr_time[i]);

                    text.display(coor.x - 20,coor.y, Window::renderer, tmp.c_str());
                }
            }
            else if (TrafficLight_list[i]->get_curr_color() == "yellow"){
                if (_curr_time[i] == 5) TrafficLight_list[i]->ChangeColor("src/images/signals/yellow.png", "yellow");
               
                _curr_time[i] = TrafficLight_list[i]->get_timer();
                TrafficLight_list[i]->set_countdowntime(_curr_time[i]);
                tmp = to_string(_curr_time[i]);
                text.display(coor.x - 20,coor.y, Window::renderer, tmp.c_str());
                //scout << _curr_time << " seconds remaining" << endl;
                cout << tmp << " " << 0 << endl;

                if (_curr_time[i] == 0) {
                    TrafficLight_list[i]->set_color("red");
                    TrafficLight_list[i]->ChangeColor("src/images/signals/red.png", "red");
                    TrafficLight_list[i]->set_countdowntime(10);
                    TrafficLight_list[i]->set_timer(10);
                    _curr_time[i] = 10;
                    tmp = to_string(_curr_time[i]);

                    text.display(coor.x - 20,coor.y, Window::renderer, tmp.c_str());
                }
            }
            else {
                text.display(coor.x - 20,coor.y, Window::renderer,"--");
            }
        }

         SDL_Event event;

        if (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_a ) {
                    if (TrafficLight_list[0]->get_curr_color() == "red") TrafficLight_list[0]->set_color("green");
                    else if (TrafficLight_list[0]->get_curr_color() == "green") {
                        TrafficLight_list[0]->set_countdowntime(10);
                        TrafficLight_list[0]->set_timer(10);
                        _curr_time[0] = 10;
                    }
                }
                else if (event.key.keysym.sym == SDLK_w) {
                    if (TrafficLight_list[1]->get_curr_color() == "red") TrafficLight_list[1]->set_color("green");
                    else if (TrafficLight_list[1]->get_curr_color() == "green") {
                        TrafficLight_list[1]->set_countdowntime(10);
                        TrafficLight_list[1]->set_timer(10);
                        _curr_time[1] = 10;
                    }
                }
                else if (event.key.keysym.sym == SDLK_s) {
                    if (TrafficLight_list[2]->get_curr_color() == "red") TrafficLight_list[2]->set_color("green");
                    else if (TrafficLight_list[2]->get_curr_color() == "green") {
                        TrafficLight_list[2]->set_countdowntime(10);
                        TrafficLight_list[2]->set_timer(10);
                        _curr_time[2] = 10;
                    }
                }
                else if (event.key.keysym.sym == SDLK_d) {
                    if (TrafficLight_list[3]->get_curr_color() == "red") TrafficLight_list[3]->set_color("green");
                    else if (TrafficLight_list[3]->get_curr_color() == "green") {
                        TrafficLight_list[3]->set_countdowntime(10);
                        TrafficLight_list[3]->set_timer(10);
                        _curr_time[3] = 10;
                    }
                } 
            }
        }

        // road1.pollEvents(SDLK_a);
        // road2.pollEvents(SDLK_w);
        // road3.pollEvents(SDLK_s);
        // road4.pollEvents(SDLK_d);

        window.pollEvents();
        window.clear();
    }



}