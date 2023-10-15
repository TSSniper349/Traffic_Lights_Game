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
#include <fstream>
#include <ctime>
#include <sstream>
#include <cstring>
#include <iostream>
using namespace std;

bool saveScreenshot(SDL_Renderer* renderer, const char* filename) {
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    SDL_Surface* screenshot = SDL_CreateRGBSurface(0, width, height, 32, 
                                                   0x00FF0000, 
                                                   0x0000FF00, 
                                                   0x000000FF, 
                                                   0xFF000000);
    if (!screenshot) {
        SDL_Log("Unable to create screenshot surface: %s", SDL_GetError());
        return false;
    }

    if (SDL_RenderReadPixels(renderer, NULL, screenshot->format->format, screenshot->pixels, screenshot->pitch) != 0) {
        SDL_Log("Unable to read pixels from renderer: %s", SDL_GetError());
        SDL_FreeSurface(screenshot);
        return false;
    }

    if (IMG_SavePNG(screenshot, filename) != 0) {
        SDL_Log("Unable to save image: %s", IMG_GetError());
        SDL_FreeSurface(screenshot);
        return false;
    }

    SDL_FreeSurface(screenshot);
    return true;
}


void saveScore(int score) {
    std::ofstream file("score_data.txt", std::ios::app);  // Note the 'std::ios::app' mode

    if (!file.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    // Get the current date and time
    std::time_t now = std::time(nullptr);
    char* dt = std::ctime(&now);
    
    // Remove newline that ctime adds
    dt[strlen(dt) - 1] = '\0';

    file << score << " " << dt << std::endl;

    file.close();
}

int GetBestScore() {
    std::ifstream file("score_data.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return -1; // Return a value indicating the error
    }

    int bestScore = 0;   // Assuming scores are non-negative. Initialize with a value lower than possible scores if not.
    int currentScore;
    std::string temp;
    while (getline(file, temp)) {
        std::istringstream iss(temp);
        iss >> currentScore;
        if (currentScore > bestScore) {
            bestScore = currentScore;
        }
    }

    file.close();

    if (bestScore > 0) {  // or just check if bestScore is not its initial value, depending on your requirements
        std::cout << "Best Score: " << bestScore << std::endl;
        return bestScore;
    } else {
        std::cout << "No scores found." << std::endl;
        return 0; // Return a value indicating no score found
    }
}




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
    SDL_Texture* restart_img = window.loadTexture("res/gfx/restart_button.png");

    TrafficLight *trafficlightLeft = new TrafficLight(window.render(), 340, 320, "res/gfx/red.png", 6);
    TrafficLight *trafficlightTop = new TrafficLight(window.render(), 590, 320, "res/gfx/red.png", 6);
    TrafficLight *trafficlightBottom = new TrafficLight(window.render(), 340, 590, "res/gfx/red.png", 6);
    TrafficLight *trafficlightRight = new TrafficLight(window.render(), 590, 590, "res/gfx/red.png", 6);

    Enity mainBackground(Coordination(0, 0), mainBg);
    Enity restartButton(Coordination(420,565), restart_img);
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
    float spawn_speed = 0.000f;

    Roads[0].add_TrafficLight(trafficlightLeft);
    Roads[1].add_TrafficLight(trafficlightRight);
    Roads[2].add_TrafficLight(trafficlightTop);
    Roads[3].add_TrafficLight(trafficlightBottom);

    int check = 0;
    // CountdownTimer timer(10);
    int _curr_time[4] = {6, 6, 6, 6};
    Text cntLight[4];

    float currentTime = utils::hireTimeInSeconds();
    srand(time(0));

    bool _gameOver = false;
    SDL_Texture* gameOverBg;
    Enity gameOverBackGround;
    string _gameOver_score = "";
    string _Best_score = "";
    string _curr_score = "";
    bool oneTimeAction = true;
    
    Text gameOver_text;
    Text Best_score;
    Text curr_score;

    while (gameRunning)
    {
        if (_gameOver){
            if (oneTimeAction == true){
                gameOverBg = window.loadTexture("screenshot.png");
                gameOverBackGround = Enity(Coordination(0,0),gameOverBg);

                gameOver_text = Text(window.render(),"res/dev/Blockletter.otf",100,"Game Over", {51,0,0});
            
                
                _Best_score = "Best score: " + to_string(GetBestScore());
                Best_score = Text(window.render(),"res/dev/Blockletter.otf", 50, _Best_score, {82,82,82});
                _curr_score =  "Score: " + to_string(_score);
                curr_score = Text(window.render(),"res/dev/Blockletter.otf", 50, _curr_score, {82,82,82});
                oneTimeAction = false;

            }

            float startTick = SDL_GetTicks64();

            float newTime = utils::hireTimeInSeconds();
            float frameTime = newTime - currentTime;

            currentTime = newTime;
            accumulator += frameTime;



            while(accumulator >= timeStep) {
                while(SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) gameRunning = false;
                    else if(event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    if(mouseX >= restartButton.get_pos().x && mouseX <= (restartButton.get_pos().x + restartButton.get_frame().w) &&
                    mouseY >= restartButton.get_pos().y && mouseY <= (restartButton.get_pos().y + restartButton.get_frame().h)) {
                        // The restart button was clicked
                        // gameRunning = false;
                        for (short int i = 0; i < 4; i++){
                            for (short int j = 0; j < 3; j++){
                                (Roads[i].get_list_of_lane()+j)->clear_vehicle();
                            }
                        }
                        for (short int i = 0; i < 4; i++){
                            (Roads[i].get_trafficlight())->set_countdowntime(6);
                            (Roads[i].get_trafficlight())->set_timer(6);
                            _curr_time[i] = 6;
                            (Roads[i].get_trafficlight())->ChangeColor(window.render(),"res/gfx/red.png", "red");
                        }
                        _score = 0;
                        _gameOver = false;
                        oneTimeAction = true;
                    }
                }
                }
                
                accumulator -= timeStep;
            }

            
            
            float frameTicks = SDL_GetTicks64() - startTick;

            if(frameTicks < 1000/ window.getRefreshRate()) {
                SDL_Delay(1000/window.getRefreshRate() - frameTicks);
            }

            window.clear();
            window.renderBackground(gameOverBackGround);
            window.renderButton(restartButton);

            gameOver_text.display(280,350, window.render());
            Best_score.display(350,500, window.render());
            curr_score.display(350,450, window.render());
            
            window.display();

            continue;
        }
        float startTick = SDL_GetTicks64();

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;
        accumulator2 += frameTime;
        spawnTime += frameTime;

        while (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_a &&
                Roads[1].get_trafficlight()->get_curr_color() == "red" &&
                Roads[2].get_trafficlight()->get_curr_color() == "red" &&
                Roads[3].get_trafficlight()->get_curr_color() == "red")
            {
                // cout<<"1";
                if (Roads[0].get_trafficlight()->get_curr_color() == "red")
                    Roads[0].get_trafficlight()->set_color("green");
                else if (Roads[0].get_trafficlight()->get_curr_color() == "green")
                {
                    Roads[0].get_trafficlight()->set_countdowntime(6);
                    Roads[0].get_trafficlight()->set_timer(6);
                    _curr_time[0] = 6;
                }
            }
            else if (event.key.keysym.sym == SDLK_d &&
                     Roads[0].get_trafficlight()->get_curr_color() == "red" &&
                     Roads[2].get_trafficlight()->get_curr_color() == "red" &&
                     Roads[3].get_trafficlight()->get_curr_color() == "red")
            {
                if (Roads[1].get_trafficlight()->get_curr_color() == "red")
                    Roads[1].get_trafficlight()->set_color("green");
                else if (Roads[1].get_trafficlight()->get_curr_color() == "green")
                {
                    Roads[1].get_trafficlight()->set_countdowntime(6);
                    Roads[1].get_trafficlight()->set_timer(6);
                    _curr_time[1] = 6;
                }
            }
            else if (event.key.keysym.sym == SDLK_w &&
                     Roads[0].get_trafficlight()->get_curr_color() == "red" &&
                     Roads[1].get_trafficlight()->get_curr_color() == "red" &&
                     Roads[3].get_trafficlight()->get_curr_color() == "red")
            {
                if (Roads[2].get_trafficlight()->get_curr_color() == "red")
                    Roads[2].get_trafficlight()->set_color("green");
                else if (Roads[2].get_trafficlight()->get_curr_color() == "green")
                {
                    Roads[2].get_trafficlight()->set_countdowntime(6);
                    Roads[2].get_trafficlight()->set_timer(6);
                    _curr_time[2] = 6;
                }
            }
            else if (event.key.keysym.sym == SDLK_s &&
                     Roads[0].get_trafficlight()->get_curr_color() == "red" &&
                     Roads[1].get_trafficlight()->get_curr_color() == "red" &&
                     Roads[2].get_trafficlight()->get_curr_color() == "red")
            {
                if (Roads[3].get_trafficlight()->get_curr_color() == "red")
                    Roads[3].get_trafficlight()->set_color("green");
                else if (Roads[3].get_trafficlight()->get_curr_color() == "green")
                {
                    Roads[3].get_trafficlight()->set_countdowntime(6);
                    Roads[3].get_trafficlight()->set_timer(6);
                    _curr_time[3] = 6;
                }
            }
        }

        if (_score <= 100)
        {
            spawn_speed = 80;
        }
        else if (_score <= 300)
        {
            spawn_speed = 60;
        }
        else if (_score <= 600)
        {
            spawn_speed = 45;
        }
        else if (_score <= 1000)
        {
            spawn_speed = 35;
        }
        else
        {
            spawn_speed = 30;
        }

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
                            if (x == (Roads[0].get_list_of_lane() + 0)->get_list_vehicles()->begin()){
                                //cout << "Length of first vehicle in roads 0 lane 0: " << (Roads[0].get_list_of_lane() + 0)->get_curr_length() << endl;
                            }
                            string curr_col = Roads[i].get_trafficlight()->get_curr_color();
                            if (curr_pos.x >= 370 && curr_pos.x <= 590 && curr_pos.y >= 370 && curr_pos.y <= 590 && x->get_through() == false)
                            {
                                (Roads[i].get_list_of_lane() + j)->vehicleThrough(x);
                                x->set_through();

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
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos.x <= 369.8 || curr_pos.x >= 372)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else 
                                        {
                                            Coordination vehicle_ahead = (x - 1)->get_pos();
                                            float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                            if (dist >= (x - 1)->get_length() + 6.0) x->go();
                                            else if (x->get_have_add() == false){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                            }
                                        }
                                    }
                                    else if (x->get_have_add() == false && x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin()){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                    }
                                }
                                if (dir == 1)
                                {
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos.x <= 588 || curr_pos.x >= 590.2)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            Coordination vehicle_ahead = (x - 1)->get_pos();
                                            float dist = sqrt(pow(abs(vehicle_ahead.x - curr_pos.x), 2) + pow(abs(vehicle_ahead.y - curr_pos.y), 2));
                                            if (dist >= (x - 1)->get_length() + 6.0) x->go();
                                            else if (x->get_have_add() == false){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                            }
                                        }
                                    }
                                    else if (x->get_have_add() == false && x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin()){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                    }
                                }
                                if (dir == 2)
                                {
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos.y <= 369.8 || curr_pos.y >= 372)))
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
                                            else if (x->get_have_add() == false){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                            }
                                        }
                                    }
                                    else if (x->get_have_add() == false && x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin()){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                    }
                                }
                                if (dir == 3)
                                {
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos.y >= 590.2 || curr_pos.y <= 588)))
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
                                            else if (x->get_have_add() == false){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                            }
                                        }
                                    }
                                    else if (x->get_have_add() == false && x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin()){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
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
                      FILE *f = fopen("screenshot.png", "r");
                        if (f) {
                            cout << 1 << endl;
                            remove("screenshot.png");
                            fclose(f);
                        }
                        saveScreenshot(window.render(), "screenshot.png");
                        saveScore(_score);
                        cout <<"Road " << i << " Lane " << j << " full" << endl;
                        cout << "Length of full lane: " << (Roads[i].get_list_of_lane() + j)->get_curr_length() << endl;
                        _gameOver = true;  
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

        if (spawnTime >= spawn_speed * timeStep)
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
            if (rand2 == 1)
            {
                Car p_vehicle = Car(spawn_pos, rand0, rand1, 2, carImg_1);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            if (rand2 == 2)
            {
                Car p_vehicle = Car(spawn_pos, rand0, rand1, 3, carImg_2);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            if (rand2 == 3)
            {
                Car p_vehicle = Car(spawn_pos, rand0, rand1, 4, carImg_3);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 4)
            {
                Bus p_vehicle = Bus(spawn_pos, rand0, rand1, 5, busImg_0);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 5)
            {
                Bus p_vehicle = Bus(spawn_pos, rand0, rand1, 6, busImg_1);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 6)
            {
                Bus p_vehicle = Bus(spawn_pos, rand0, rand1, 7, busImg_2);
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
            spawnTime -= spawn_speed * timeStep;
        }

        window.clear();
        window.renderBackground(mainBackground);
        window.renderVehicle(vehicles);
        main_score.display(20, 20, window.render());

        for (short int i = 0; i < 4; i++)
        {
            Coordination pos = Roads[i].get_trafficlight()->get_pos();
            if (Roads[i].get_trafficlight()->get_curr_color() == "green")
            {
                if (_curr_time[i] == 6)
                    Roads[i].get_trafficlight()->ChangeColor(window.render(), "res/gfx/green.png", "green");

                _curr_time[i] = Roads[i].get_trafficlight()->get_timer();
                Roads[i].get_trafficlight()->set_countdowntime(_curr_time[i]);
                cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {50, 50, 50});

                if (_curr_time[i] == 0)
                {
                    Roads[i].get_trafficlight()->set_color("yellow");
                    Roads[i].get_trafficlight()->set_countdowntime(2);
                    Roads[i].get_trafficlight()->set_timer(2);
                    _curr_time[i] = 2;
                    cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {50, 50, 50});
                }
                cntLight[i].display(pos.x + 6, pos.y - 24, window.render());
            }
            else if (Roads[i].get_trafficlight()->get_curr_color() == "yellow")
            {
                if (_curr_time[i] == 2)
                    Roads[i].get_trafficlight()->ChangeColor(window.render(), "res/gfx/yellow.png", "yellow");

                _curr_time[i] = Roads[i].get_trafficlight()->get_timer();
                Roads[i].get_trafficlight()->set_countdowntime(_curr_time[i]);
                cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {50, 50, 50});
                // scout << _curr_time << " seconds remaining" << endl;
                // cout << tmp << " " << 0 << endl;

                if (_curr_time[i] == 0)
                {
                    Roads[i].get_trafficlight()->set_color("red");
                    Roads[i].get_trafficlight()->ChangeColor(window.render(), "res/gfx/red.png", "red");
                    Roads[i].get_trafficlight()->set_countdowntime(6);
                    Roads[i].get_trafficlight()->set_timer(6);
                    _curr_time[i] = 6;
                    cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {50, 50, 50});
                }
                cntLight[i].display(pos.x + 6, pos.y - 24, window.render());
            }
            else
            {
                Text nothing = Text(window.render(), "res/dev/Blockletter.otf", 18, "--", {50, 50, 50});
                nothing.display(pos.x + 5, pos.y - 20, window.render());
            }
        }
        for (short int i = 0; i < 4; i++)
        {
            Roads[i].get_trafficlight()->display(window.render());
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
