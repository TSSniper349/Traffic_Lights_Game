#include <string>
#include "Lane.h"
#include "Utils.h"
#include "Text.h"
#include <vector>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include "RenderWindow.h"
#include "Car.h"
#include "Bus.h"
#include "Motorbike.h"
#include "Enity.h"
#include "Road.h"
using namespace std;

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMGE_INIT HAS FAILED. Error: " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() == -1)
    {
        std::cout << "TTF_INIT HAS FAILED. Error: " << SDL_GetError() << std::endl;
    }

    RenderWindow window("Traffices", 960, 960);

    SDL_Texture *mainBg = window.loadTexture("res/gfx/main-bg.png");
    SDL_Texture *carImg_0 = window.loadTexture("res/gfx/carImg_0.png");
    SDL_Texture *carImg_1 = window.loadTexture("res/gfx/carImg_1.png");
    SDL_Texture *carImg_2 = window.loadTexture("res/gfx/carImg_2.png");
    SDL_Texture *carImg_3 = window.loadTexture("res/gfx/carImg_3.png");
    SDL_Texture *busImg_0 = window.loadTexture("res/gfx/busImg_0.png");
    SDL_Texture *busImg_1 = window.loadTexture("res/gfx/busImg_1.png");
    SDL_Texture *busImg_2 = window.loadTexture("res/gfx/busImg_2.png");
    SDL_Texture *motorImg_0 = window.loadTexture("res/gfx/motorImg_0.png");
    SDL_Texture *motorImg_1 = window.loadTexture("res/gfx/motorImg_1.png");
    SDL_Texture *motorImg_2 = window.loadTexture("res/gfx/motorImg_2.png");

    TrafficLight *trafficlightLeft = new TrafficLight(window.render(), 340, 330, "res/gfx/red.png", 6);
    TrafficLight *trafficlightTop = new TrafficLight(window.render(), 590, 330, "res/gfx/red.png", 6);
    TrafficLight *trafficlightBottom = new TrafficLight(window.render(), 340, 590, "res/gfx/red.png", 6);
    TrafficLight *trafficlightRight = new TrafficLight(window.render(), 590, 590, "res/gfx/red.png", 6);

    Enity mainBackground(Coordination(0, 0), mainBg);
    std::vector<Vehicle> *vehicles = new std::vector<Vehicle>;

    Road Roads[4] = {Road("Left"),
                     Road("Right"),
                     Road("Top"),
                     Road("Bottom")};

    int _score = 0;
    std::string _main_score = "";

    bool gameRunning = true;
    SDL_Event event;

    const float timeStep = 0.007f;
    const float timeStep2 = 0.001f;
    float accumulator = 0.0f;
    float accumulator2 = 0.0f;
    float spawnTime = 0.0f;

    Roads[0].add_TrafficLight(trafficlightLeft);
    Roads[1].add_TrafficLight(trafficlightRight);
    Roads[2].add_TrafficLight(trafficlightTop);
    Roads[3].add_TrafficLight(trafficlightBottom);

    TrafficLight **TrafficLight_list;
    for (short int i = 0; i < 4; i++)
    {
        TrafficLight_list[i] = Roads[i].get_trafficlight();
    }

    int check = 0;
    // CountdownTimer timer(10);
    int _curr_time[4] = {6, 6, 6, 6};
    Text cntLight[4];

    float currentTime = utils::hireTimeInSeconds();
    srand(time(0));

    while (gameRunning)
    {

        while (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_a)
            {
                // cout<<"1";
                if (TrafficLight_list[0]->get_curr_color() == "red")
                    TrafficLight_list[0]->set_color("green");
                else if (TrafficLight_list[0]->get_curr_color() == "green")
                {
                    TrafficLight_list[0]->set_countdowntime(6);
                    TrafficLight_list[0]->set_timer(6);
                    _curr_time[0] = 6;
                }
            }
            else if (event.key.keysym.sym == SDLK_d)
            {
                if (TrafficLight_list[1]->get_curr_color() == "red")
                    TrafficLight_list[1]->set_color("green");
                else if (TrafficLight_list[1]->get_curr_color() == "green")
                {
                    TrafficLight_list[1]->set_countdowntime(6);
                    TrafficLight_list[1]->set_timer(6);
                    _curr_time[1] = 6;
                }
            }
            else if (event.key.keysym.sym == SDLK_w)
            {
                if (TrafficLight_list[2]->get_curr_color() == "red")
                    TrafficLight_list[2]->set_color("green");
                else if (TrafficLight_list[2]->get_curr_color() == "green")
                {
                    TrafficLight_list[2]->set_countdowntime(6);
                    TrafficLight_list[2]->set_timer(6);
                    _curr_time[2] = 6;
                }
            }
            else if (event.key.keysym.sym == SDLK_s)
            {
                if (TrafficLight_list[3]->get_curr_color() == "red")
                    TrafficLight_list[3]->set_color("green");
                else if (TrafficLight_list[3]->get_curr_color() == "green")
                {
                    TrafficLight_list[3]->set_countdowntime(6);
                    TrafficLight_list[3]->set_timer(6);
                    _curr_time[3] = 6;
                }
            }
        }

        float startTick = SDL_GetTicks64();

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;
        accumulator2 += frameTime;
        spawnTime += frameTime;
        _main_score = "Score: " + to_string(_score);
        Text main_score(window.render(), "res/dev/Blockletter.otf", 25, _main_score, {82, 82, 82});

        while (accumulator2 >= timeStep2)
        {
            for (short int i = 0; i < 4; i++)
            {
                for (short int j = 0; j < 3; j++)
                {
                    if ((Roads[i].get_list_of_lane() + j)->get_list_vehicles()->size())
                    {
                        std::vector<Vehicle>::iterator x;
                        for (x = (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin(); x < (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->end(); x++)
                        {
                            Coordination curr_pos = x->get_pos();
                            short int p_lane = x->get_lane();
                            float length = x->get_length();
                            short int dir = x->get_direction();
                            string curr_col = TrafficLight_list[i]->get_curr_color();
                            if (curr_pos.x >= 370 && curr_pos.x <= 590 && curr_pos.y >= 370 && curr_pos.y <= 590)
                            {
                                (Roads[i].get_list_of_lane() + j)->vehicleThrough(x);
                            }
                            if (curr_pos.x >= 370 && curr_pos.x <= 590 && curr_pos.y >= 370 && curr_pos.y <= 590 && p_lane % 3 == 0)
                            {
                                if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                    x->turnLeft();
                                else
                                {
                                    Coordination vehicle_ahead = (x - 1)->get_pos();
                                    float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                    if (dist >= (x - 1)->get_length() + 5)
                                        x->turnLeft();
                                }
                            }
                            else if (curr_pos.x >= 370 && curr_pos.x <= 590 && curr_pos.y >= 370 && curr_pos.y <= 590 && p_lane % 3 == 2)
                            {
                                (Roads[i].get_list_of_lane() + j)->vehicleThrough(x);
                                if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                    x->turnRight();
                                else
                                {
                                    Coordination vehicle_ahead = (x - 1)->get_pos();
                                    float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                    if (dist >= (x - 1)->get_length() + 5)
                                        x->turnRight();
                                }
                            }
                            else
                            {
                                if (dir == 0)
                                {
                                    if (curr_col == "green" || curr_col == "yellow" || (curr_col == "red" && (curr_pos.x <= 369.8 || curr_pos.x >= 372)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            Coordination vehicle_ahead = (x - 1)->get_pos();
                                            float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                            if (dist >= (x - 1)->get_length() + 6.0)
                                                x->go();
                                        }
                                    }
                                }
                                if (dir == 1)
                                {
                                    if (curr_col == "green" || curr_col == "yellow" || (curr_col == "red" && (curr_pos.x <= 588 || curr_pos.x >= 590.2)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            Coordination vehicle_ahead = (x - 1)->get_pos();
                                            float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                            if (dist >= (x - 1)->get_length() + 6.0)
                                                x->go();
                                        }
                                    }
                                }
                                if (dir == 2)
                                {
                                    if (curr_col == "green" || curr_col == "yellow" || (curr_col == "red" && (curr_pos.y <= 369.8 || curr_pos.y >= 372)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            Coordination vehicle_ahead = (x - 1)->get_pos();
                                            float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                            if (dist >= (x - 1)->get_length() + 6.0)
                                                x->go();
                                        }
                                    }
                                }
                                if (dir == 3)
                                {
                                    if (curr_col == "green" || curr_col == "yellow" || (curr_col == "red" && (curr_pos.y >= 590.2 || curr_pos.y <= 588)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            Coordination vehicle_ahead = (x - 1)->get_pos();
                                            float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                            if (dist >= (x - 1)->get_length() + 6.0)
                                                x->go();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            accumulator2 -= timeStep2;
        }

        while (accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    gameRunning = false;
            }
            for (short int i = 0; i < 4; i++)
            {
                for (short int j = 0; j < 3; j++)
                {
                    if ((Roads[i].get_list_of_lane() + j)->get_curr_length() >= (Roads[i].get_list_of_lane() + j)->get_max_length())
                    {
                    }
                    std::vector<Vehicle> *vehicles_list = (Roads[i].get_list_of_lane() + j)->get_list_vehicles();
                    if (vehicles_list->size() != 0)
                    {
                        std::vector<Vehicle>::iterator x;
                        for (x = vehicles_list->begin(); x < vehicles_list->end(); x++)
                        {
                            vehicles->push_back(*x);
                        }
                        Coordination curr_pos = vehicles_list->front().get_pos();
                        if (curr_pos.x > 1040 || curr_pos.x < -80 || curr_pos.y > 1040 || curr_pos.y < -80)
                        {
                            (Roads[i].get_list_of_lane() + j)->delVehicle(vehicles_list->begin());
                            _score += vehicles_list->begin()->get_capacity();
                        }
                    }
                }
            }
            accumulator -= timeStep;
        }

        if (spawnTime >= 60 * timeStep)
        {
            short int rand0 = std::rand() % 4;
            short int rand1 = std::rand() % 3;
            short int rand2 = std::rand() % 10;
            Coordination spawn_pos = (Roads[rand0].get_list_of_lane() + rand1)->get_pos();
            if (rand2 == 0)
            {
                Car p_vehicle = Car(spawn_pos, rand0, rand1, 1, carImg_0);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 4)
            {
                Bus p_vehicle = Bus(spawn_pos, rand0, rand1, 10, busImg_0);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 5)
            {
                Bus p_vehicle = Bus(spawn_pos, rand0, rand1, 10, busImg_1);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 6)
            {
                Bus p_vehicle = Bus(spawn_pos, rand0, rand1, 10, busImg_2);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 7)
            {
                Motorbike p_vehicle = Motorbike(spawn_pos, rand0, rand1, motorImg_0);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 8)
            {
                Motorbike p_vehicle = Motorbike(spawn_pos, rand0, rand1, motorImg_1);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 9)
            {
                Motorbike p_vehicle = Motorbike(spawn_pos, rand0, rand1, motorImg_2);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            // std::cout<<lane[rand].get_curr_length();
            spawnTime -= 60 * timeStep;
        }

        window.clear();
        window.renderBackground(mainBackground);
        window.renderVehicle(vehicles);
        main_score.display(20, 20, window.render());

        for (short int i = 0; i < 4; i++)
        {
            Coordination pos = TrafficLight_list[i]->get_pos();
            if (TrafficLight_list[i]->get_curr_color() == "green")
            {
                if (_curr_time[i] == 6)
                    TrafficLight_list[i]->ChangeColor(window.render(), "res/gfx/green.png", "green");

                _curr_time[i] = TrafficLight_list[i]->get_timer();
                TrafficLight_list[i]->set_countdowntime(_curr_time[i]);
                cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {82, 82, 82});

                if (_curr_time[i] == 0)
                {
                    TrafficLight_list[i]->set_color("yellow");
                    TrafficLight_list[i]->set_countdowntime(2);
                    TrafficLight_list[i]->set_timer(2);
                    _curr_time[i] = 2;
                    cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {82, 82, 82});
                }
                cntLight[i].display(pos.x + 9, pos.y - 25, window.render());
            }
            else if (TrafficLight_list[i]->get_curr_color() == "yellow")
            {
                if (_curr_time[i] == 2)
                    TrafficLight_list[i]->ChangeColor(window.render(), "res/gfx/yellow.png", "yellow");

                _curr_time[i] = TrafficLight_list[i]->get_timer();
                TrafficLight_list[i]->set_countdowntime(_curr_time[i]);
                cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {82, 82, 82});
                // scout << _curr_time << " seconds remaining" << endl;
                // cout << tmp << " " << 0 << endl;

                if (_curr_time[i] == 0)
                {
                    TrafficLight_list[i]->set_color("red");
                    TrafficLight_list[i]->ChangeColor(window.render(), "res/gfx/red.png", "red");
                    TrafficLight_list[i]->set_countdowntime(6);
                    TrafficLight_list[i]->set_timer(6);
                    _curr_time[i] = 6;
                    cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {82, 82, 82});
                }
                cntLight[i].display(pos.x + 9, pos.y - 25, window.render());
            }
            else
            {
                Text nothing = Text(window.render(), "res/dev/Blockletter.otf", 18, "--", {50, 50, 50});
                nothing.display(pos.x + 8, pos.y - 20, window.render());
            }
        }
        for (short int i = 0; i < 4; i++)
        {
            TrafficLight_list[i]->display(window.render());
        }

        window.display();
        vehicles->clear();

        float frameTicks = SDL_GetTicks64() - startTick;

        if (frameTicks < 1000 / window.getRefreshRate())
        {
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
        }
    }

    window.CleanUp();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
