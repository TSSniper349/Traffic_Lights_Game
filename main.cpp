#include <iostream>
#include<string>
#include <cstdlib>
#include<time.h>
#include"RenderWindow.h"
#include"Car.h"
#include"Bus.h"
#include"Motorbike.h"
#include"Lane.h"
#include"Enity.h"
#include"Utils.h"
#include"Initiate.h"
#include"Text.h"
#include<vector>
#include<math.h>
using namespace std;

int main( int argc, char* args[] )
{
    if(SDL_Init(SDL_INIT_VIDEO)>0) {
        std::cout<<"SDL_Init HAS FAILED. SDL_ERROR: "<<SDL_GetError()<<std::endl;
    }
    if(!(IMG_Init(IMG_INIT_PNG))) {
        std::cout<<"IMGE_INIT HAS FAILED. Error: "<<SDL_GetError()<<std::endl;
    }
    if(TTF_Init()==-1) {
        std::cout<<"TTF_INIT HAS FAILED. Error: "<<SDL_GetError()<<std::endl;
    }

    float currentTime = utils::hireTimeInSeconds();
    srand(time(0));

    while(gameRunning) {

        float startTick = SDL_GetTicks64();

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;
        accumulator2 += frameTime;
        spawnTime += frameTime;
        _main_score = "Score: " + to_string(_score);
        Text main_score(window.render(),"res/dev/Blockletter.otf", 25, _main_score, {82,82,82});

        while (accumulator2>=timeStep2)
        {
            for(short int i=0;i<4;i++) {
                for(short int j=0;j<3;j++) {
                    //std::vector<Vehicle> *vehicles_list;
                    if((Roads[i].get_list_of_lane()+j)->get_list_vehicles()->size()) {
                        std::vector<Vehicle>::iterator x;
                        for(x = (Roads[i].get_list_of_lane()+j)->get_list_vehicles()->begin(); x < (Roads[i].get_list_of_lane()+j)->get_list_vehicles()->end(); x++) {
                            Coordination curr_pos = x->get_pos();
                            short int p_lane = x->get_lane();
                            if(curr_pos.x>=370&&curr_pos.x<=560&&curr_pos.y>=370&&curr_pos.y<=560&&p_lane%3==0) {
                                x->turnLeft();
                            }
                            else if(curr_pos.x>=400&&curr_pos.x<=530&&curr_pos.y>=400&&curr_pos.y<=530&&p_lane%3==2) {
                                x->turnRight();
                            }
                            else {
                                if(x == (Roads[i].get_list_of_lane()+j)->get_list_vehicles()->begin()) {x->go();}
                                else {
                                    Coordination vehicle_ahead = (x-1)->get_pos();
                                    short int dir = x->get_direction();
                                    float dist = sqrt(pow(abs(vehicle_ahead.x-curr_pos.x),2)+pow(abs(vehicle_ahead.y-curr_pos.y),2));
                                    if((dir==0||dir==2)&&dist>=(x-1)->get_length()+8) x->go();
                                    else if((dir==1||dir==3)&&dist>=(x-1)->get_length()+8) x->go();
                                }
                            }
                        }
                    }
                }
            }
            accumulator2-=timeStep2;
        }
        

        while(accumulator >= timeStep) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) gameRunning = false;
            }
            accumulator -= timeStep;
            for(short int i=0;i<4;i++) {
                for(short int j=0;j<3;j++) {
                    if((Roads[i].get_list_of_lane()+j)->get_curr_length()>=(Roads[i].get_list_of_lane()+j)->get_max_length()) {}
                    std::vector<Vehicle> *vehicles_list = (Roads[i].get_list_of_lane()+j)->get_list_vehicles();
                    if(vehicles_list->size()!=0) {
                        std::vector<Vehicle>::iterator x;
                        for(x = vehicles_list->begin(); x < vehicles_list->end(); x++) {
                            vehicles->push_back(*x);
                        }
                        Coordination curr_pos = vehicles_list->front().get_pos();
                        if(curr_pos.x>965||curr_pos.x<-40||curr_pos.y>965||curr_pos.y<-40) {
                            (Roads[i].get_list_of_lane()+j)->delVehicle(vehicles_list->begin());
                            _score++;
                        }
                    }
                }
            }
        }

        if (spawnTime >= 60*timeStep) {
            short int rand0 = std::rand()%4;
            short int rand1 = std::rand()%3;
            short int rand2 = std::rand()%10;
            Coordination spawn_pos = (Roads[rand0].get_list_of_lane()+rand1)->get_pos();
            if(rand2==0){
                Car p_vehicle = Car(spawn_pos,rand0,rand1,1,carImg_0);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==1) {
                Car p_vehicle = Car(spawn_pos,rand0,rand1,2,carImg_1);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==2) {
                Car p_vehicle = Car(spawn_pos,rand0,rand1,3,carImg_2);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==3) {
                Car p_vehicle = Car(spawn_pos,rand0,rand1,4,carImg_3);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==4) {
                Bus p_vehicle = Bus(spawn_pos,rand0,rand1,1,busImg_0);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==5) {
                Bus p_vehicle = Bus(spawn_pos,rand0,rand1,1,busImg_1);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==6) {
                Bus p_vehicle = Bus(spawn_pos,rand0,rand1,1,busImg_2);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==7) {
                Motorbike p_vehicle = Motorbike(spawn_pos,rand0,rand1,motorImg_0);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==8) {
                Motorbike p_vehicle = Motorbike(spawn_pos,rand0,rand1,motorImg_1);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            else if(rand2==9) {
                Motorbike p_vehicle = Motorbike(spawn_pos,rand0,rand1,motorImg_2);
                (Roads[rand0].get_list_of_lane()+rand1)->addVehicle(p_vehicle);
            }
            //std::cout<<lane[rand].get_curr_length();
            spawnTime -= 60*timeStep;
        }

        window.clear();
        window.renderBackground(mainBackground);
        window.renderVehicle(vehicles);
        main_score.display(20,20, window.render());
        window.display();

        vehicles->clear();

        float frameTicks = SDL_GetTicks64() - startTick;

        if(frameTicks < 1000/ window.getRefreshRate()) {
            SDL_Delay(1000/window.getRefreshRate() - frameTicks);
        }
    }

    window.CleanUp();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
