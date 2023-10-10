#include <iostream>
#include <cstdlib>
#include<time.h>
#include"RenderWindow.h"
#include"Car.h"
#include"Bus.h"
#include"Motorbike.h"
#include"Enity.h"
#include"Road.h"

RenderWindow window("Traffices", 960, 960);

SDL_Texture* mainBg = window.loadTexture("res/gfx/main-bg.png");
SDL_Texture* carImg_0 = window.loadTexture("res/gfx/carImg_0.png");
SDL_Texture* carImg_1 = window.loadTexture("res/gfx/carImg_1.png");
SDL_Texture* carImg_2 = window.loadTexture("res/gfx/carImg_2.png");
SDL_Texture* carImg_3 = window.loadTexture("res/gfx/carImg_3.png");
SDL_Texture* busImg_0 = window.loadTexture("res/gfx/busImg_0.png");
SDL_Texture* busImg_1 = window.loadTexture("res/gfx/busImg_1.png");
SDL_Texture* busImg_2 = window.loadTexture("res/gfx/busImg_2.png");   
SDL_Texture* motorImg_0 = window.loadTexture("res/gfx/motorImg_0.png");
SDL_Texture* motorImg_1 = window.loadTexture("res/gfx/motorImg_1.png");
SDL_Texture* motorImg_2 = window.loadTexture("res/gfx/motorImg_2.png");

Enity mainBackground(Coordination(0,0),mainBg);
std::vector<Vehicle> *vehicles = new std::vector<Vehicle>;

Road Roads[4] ={Road("Left"),
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