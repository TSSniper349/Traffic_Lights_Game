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
#include "UnitTesting.h"
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cstring>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include "Button.h"
#include "HighScores.h"
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
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_c);

    // Use a string stream to format the date
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << local_time->tm_mday << "/"
        << std::setw(2) << (local_time->tm_mon + 1) << "/"
        << std::setw(2) << (local_time->tm_year % 100);

    // Convert the string stream to a string
    std::string formattedDate = oss.str();

    std::ofstream file("score_data.txt", std::ios::app); 
    if (!file.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    file<< formattedDate <<" " <<"Player1"<<" "<< score<<std::endl;
    file.close();
}

int GetBestScore() {
    std::ifstream file("score_data.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return -1; // Return a value indicating the error
    }

    int bestScore = 0;   // Assuming scores are non-negative. Initialize with a value lower than possible scores if not.
    string dt,name;
    int currentScore;
    std::string temp;
    while (getline(file, temp)) {
        std::istringstream iss(temp);
        iss >>dt>>name>> currentScore;
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

    UnitTest unitTest;
    unitTest.runTests(); 

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

    Enity mainBackground(0,0, mainBg);
    Enity restartButton(420,565, restart_img);
    std::vector<Vehicle> *vehicles = new std::vector<Vehicle>;

    Road Roads[4] = {Road("Left"),
                     Road("Right"),
                     Road("Top"),
                     Road("Bottom")};

    Text gameTitle(window.render(), "res/dev/Blockletter.otf", 72, "TRAFFIC LIGHTS GAME", {68, 34, 32});
    Text highscoresTitle(window.render(), "res/dev/Blockletter.otf", 72, "HIGH SCORES", {68, 34, 32});
    Text Date(window.render(), "res/dev/Blockletter.otf", 40, "Date", { 50, 50, 50});
    Text Player(window.render(), "res/dev/Blockletter.otf", 40, "Player", { 50, 50, 50});
    Text Score(window.render(), "res/dev/Blockletter.otf", 40, "Score", { 50, 50, 50});
    Text instructionTitle(window.render(), "res/dev/Blockletter.otf", 72, "INSTRUCTION", {68, 34, 32});
    string instructionText = "Objective:\n - To control the traffic lights and manage the flow of traffic.\nControl:\n - Use the W, A, S, D key to control the traffic light at the\n top, left, bottom, right lane respectively.\n - Only 1 traffic light is allowed to turn on at a time.\nScoring:\n - Motorbikes give 1 pt, cars give 1-4 pts and buses give 5-7 pts\n based on the vehicle's color.\nConditions:\n - The player loses the game if a lane touches the edge of the window.";
    Text instruction(window.render(), "res/dev/Blockletter.otf", 32, instructionText, { 50, 50, 50}, "Instruction");

    std::vector<Button> buttons;
    buttons.emplace_back(378, 300, 200, 50, "START", window.render());
    buttons.emplace_back(378, 400, 200, 50, "HIGH SCORES", window.render());
    buttons.emplace_back(378, 500, 200, 50, "INSTRUCTION", window.render());
    buttons.emplace_back(378, 600, 200, 50, "EXIT", window.render());

    HighScores highscoresWindow;

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
    int _curr_time[4] = {6, 6, 6, 6};
    Text cntLight[4];

    float currentTime = utils::hireTimeInSeconds();
    srand(time(0));

    bool main_menu = true;
    bool _gameOver = false;
    SDL_Texture* gameOverBg;
    Enity gameOverBackGround;
    string _gameOver_score = "";
    string _Best_score = "";
    string _curr_score = "";
    bool oneTimeAction = true;
    
    Text gameOver_text = Text(window.render(),"res/dev/Blockletter.otf",100,"Game Over", {51,0,0});
    Text Best_score;
    Text curr_score;

    while (gameRunning)
    {
        while(main_menu!=false) {
            float startTick = SDL_GetTicks64();
            float newTime = utils::hireTimeInSeconds();
            float frameTime = newTime - currentTime;
            currentTime = newTime;
            accumulator += frameTime;

            while(SDL_PollEvent(&event)) if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                for (const Button& button : buttons) {
                    if (button.IsClicked(mouseX, mouseY)) {
                        if (button.GetText() == "EXIT") {
                            gameRunning = false;
                            main_menu = false;
                        }
                        if(button.GetText() == "START") {
                            main_menu = false;
                        }
                        else if (button.GetText() == "INSTRUCTION") {
                            // Render instruction window
                            window.clear();
                            window.renderBackground(mainBackground);
                            SDL_SetRenderDrawColor(window.render(), 236, 235, 243, 255);
                            SDL_Rect windowRect = { 50, 100, 860, 760}; 
                            SDL_RenderFillRect(window.render(), &windowRect);
                            instructionTitle.display(300, 120, window.render());
                            instruction.display(80, 270, window.render());
                            window.display();

                            // Wait for a key press to exit the instruction window
                            bool instructionWindowOpen = true;
                            while (instructionWindowOpen) {
                                while (SDL_PollEvent(&event) != 0 && event.key.keysym.sym == SDLK_ESCAPE) {
                                    if (event.type == SDL_QUIT) {
                                        gameRunning = false;
                                        main_menu = false;
                                        instructionWindowOpen = false;
                                    }
                                    else if (event.type == SDL_KEYDOWN) {
                                        instructionWindowOpen = false;
                                    }
                                }
                            }
                        }
                        else if (button.GetText() == "HIGH SCORES") {
                            // Render high scores window
                            window.clear();
                            window.renderBackground(mainBackground);
                            SDL_SetRenderDrawColor(window.render(), 236, 235, 243, 255);
                            SDL_Rect windowRect = { 50, 100, 860, 760}; 
                            SDL_RenderFillRect(window.render(), &windowRect);
                            highscoresTitle.display(310, 120, window.render());

                            Date.display(130, 250, window.render());
                            Player.display(430, 250, window.render());
                            Score.display(730, 250, window.render());

                            // Render the high scores
                            int text_pos_y = 320;
                            vector<tuple<string, string, int> > highScores = highscoresWindow.readHighScoresFromFile("score_data.txt");
                            std::reverse(highScores.begin(),highScores.end());
                            for (const auto& score : highScores)
                            {
                                std::string date = std::get<0>(score);
                                std::string player = std::get<1>(score);
                                int scoreValue = std::get<2>(score);
                                std::string score_str = to_string(scoreValue);

                                Text date_data(window.render(), "res/dev/Blockletter.otf", 40, date.c_str(), {82, 82, 82});
                                Text player_data(window.render(), "res/dev/Blockletter.otf", 40, player.c_str(), {82, 82, 82});
                                Text score_data(window.render(), "res/dev/Blockletter.otf", 40, score_str.c_str(), {82, 82, 82});

                                date_data.display(110, text_pos_y, window.render());
                                player_data.display(415, text_pos_y, window.render());
                                score_data.display(755, text_pos_y, window.render());

                                text_pos_y += 50;
                                if(text_pos_y>=770) break;
                            }
                            SDL_RenderPresent(window.render());

                            // Wait for a key press to exit the highscore window
                            bool highscoresWindowOpen = true;
                            while (highscoresWindowOpen) {
                                while (SDL_PollEvent(&event) != 0 && event.key.keysym.sym == SDLK_ESCAPE) {
                                    if (event.type == SDL_QUIT) {
                                        main_menu = false;
                                        gameRunning = false;
                                        highscoresWindowOpen = false;
                                    }
                                    else if (event.type == SDL_KEYDOWN) {
                                        highscoresWindowOpen = false;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
            window.clear();
            window.renderBackground(mainBackground);
            buttons[0].Render(445, 305,window.render());
            buttons[1].Render(410, 405,window.render());
            buttons[2].Render(410, 505,window.render());
            buttons[3].Render(455, 605,window.render());
            gameTitle.display(180, 150, window.render());
            window.display();

            float frameTicks = SDL_GetTicks64() - startTick;
            if(frameTicks < 1000/ window.getRefreshRate()) {
                SDL_Delay(1000/window.getRefreshRate() - frameTicks);
            }
        }

        if (_gameOver){
            float startTick = SDL_GetTicks64();
            float newTime = utils::hireTimeInSeconds();
            float frameTime = newTime - currentTime;
            currentTime = newTime;
            accumulator += frameTime;

            if (oneTimeAction == true){
                gameOverBg = window.loadTexture("screenshot.png");
                gameOverBackGround = Enity(0,0,gameOverBg);
                _Best_score = "Best score: " + to_string(GetBestScore());
                Best_score = Text(window.render(),"res/dev/Blockletter.otf", 50, _Best_score, {231,76,60});
                _curr_score =  "Score: " + to_string(_score);
                curr_score = Text(window.render(),"res/dev/Blockletter.otf", 50, _curr_score, {231,76,60});
                oneTimeAction = false;

            }

            while(accumulator >= timeStep) {
                while(SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) gameRunning = false;
                    else if(event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    if(mouseX >= restartButton.get_pos_x() && mouseX <= (restartButton.get_pos_x() + restartButton.get_frame().w) &&
                    mouseY >= restartButton.get_pos_y() && mouseY <= (restartButton.get_pos_y() + restartButton.get_frame().h)) {
                        // The restart button was clicked
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
            else if (event.key.keysym.sym != SDLK_s && event.key.keysym.sym != SDLK_w && event.key.keysym.sym != SDLK_a && event.key.keysym.sym != SDLK_d){
                cout << "Invalid input" << endl;
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
                            float curr_pos_x = x->get_pos_x();
                            float curr_pos_y = x->get_pos_y();
                            short int p_lane = x->get_lane();
                            float length = x->get_length();
                            short int dir = x->get_direction();
                            
                            string curr_col = Roads[i].get_trafficlight()->get_curr_color();
                            if (curr_pos_x >= 370 && curr_pos_x <= 590 && curr_pos_y >= 370 && curr_pos_y <= 590 && x->get_through() == false)
                            {
                                (Roads[i].get_list_of_lane() + j)->vehicleThrough(x);
                                x->set_through();
                            }
                            if (curr_pos_x >= 370 && curr_pos_x <= 590 && curr_pos_y >= 370 && curr_pos_y <= 590 && p_lane % 3 == 0)
                            {
                                if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                    x->turnLeft();
                                else
                                {
                                    float vehicle_ahead_x = (x - 1)->get_pos_x();
                                    float vehicle_ahead_y = (x - 1)->get_pos_y();
                                    float dist = sqrt(pow(abs(vehicle_ahead_x - curr_pos_x), 2) + pow(abs(vehicle_ahead_y - curr_pos_y), 2));
                                    if (dist >= (x - 1)->get_length() + 5) x->turnLeft();
                                }
                            }
                            else if (curr_pos_x >= 370 && curr_pos_x <= 590 && curr_pos_y >= 370 && curr_pos_y <= 590 && p_lane % 3 == 2)
                            {
                                (Roads[i].get_list_of_lane() + j)->vehicleThrough(x);
                                if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                    x->turnRight();
                                else
                                {
                                    float vehicle_ahead_x = (x - 1)->get_pos_x();
                                    float vehicle_ahead_y = (x - 1)->get_pos_y();
                                    float dist = sqrt(pow(abs(vehicle_ahead_x - curr_pos_x), 2) + pow(abs(vehicle_ahead_y - curr_pos_y), 2));
                                    if (dist >= (x - 1)->get_length() + 5) x->turnRight();
                                }
                            }
                            else
                            {
                                if (dir == 0)
                                {
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos_x <= 369.8 || curr_pos_x >= 372)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else 
                                        {
                                            float vehicle_ahead_x = (x - 1)->get_pos_x();
                                            float vehicle_ahead_y = (x - 1)->get_pos_y();
                                            float dist = sqrt(pow(abs(vehicle_ahead_x - curr_pos_x), 2) + pow(abs(vehicle_ahead_y - curr_pos_y), 2));
                                            if (dist >= (x - 1)->get_length() + 6.0) x->go();
                                            else if (x->get_have_add() == false){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                            }
                                        }
                                    }
                                    else if (x->get_have_add() == false && x==(Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin()){
                                                (Roads[i].get_list_of_lane() + j)->addLength(*x);
                                                x->set_have_add();
                                    }
                                }
                                if (dir == 1)
                                {
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos_x <= 588 || curr_pos_x >= 590.2)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            float vehicle_ahead_x = (x - 1)->get_pos_x();
                                            float vehicle_ahead_y = (x - 1)->get_pos_y();
                                            float dist = sqrt(pow(abs(vehicle_ahead_x - curr_pos_x), 2) + pow(abs(vehicle_ahead_y - curr_pos_y), 2));
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
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos_y <= 369.8 || curr_pos_y >= 372)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            float vehicle_ahead_x = (x - 1)->get_pos_x();
                                            float vehicle_ahead_y = (x - 1)->get_pos_y();
                                            float dist = sqrt(pow(abs(vehicle_ahead_x - curr_pos_x), 2) + pow(abs(vehicle_ahead_y - curr_pos_y), 2));
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
                                    if (curr_col == "green" || ((curr_col == "red" || curr_col == "yellow") && (curr_pos_y >= 590.2 || curr_pos_y <= 588)))
                                    {
                                        if (x == (Roads[i].get_list_of_lane() + j)->get_list_vehicles()->begin())
                                        {
                                            x->go();
                                        }
                                        else
                                        {
                                            float vehicle_ahead_x = (x - 1)->get_pos_x();
                                            float vehicle_ahead_y = (x - 1)->get_pos_y();
                                            float dist = sqrt(pow(abs(vehicle_ahead_x - curr_pos_x), 2) + pow(abs(vehicle_ahead_y - curr_pos_y), 2));
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
            while(accumulator>=timeStep) accumulator -= timeStep;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    gameRunning = false;
            }
            for (short int i = 0; i < 4; i++)
            {
                for (short int j = 0; j < 3; j++)
                {
                    if ((Roads[i].get_list_of_lane() + j)->get_curr_length() > (Roads[i].get_list_of_lane() + j)->get_max_length())
                    {
                        FILE *f = fopen("screenshot.png", "r");
                        if (f) {
                            remove("screenshot.png");
                            fclose(f);
                        }
                        saveScreenshot(window.render(), "screenshot.png");
                        saveScore(_score);
                        cout <<"Road " << i << " Lane " << j << " full" << endl;
                        cout << "Length of this lane: " << (Roads[i].get_list_of_lane() + j)->get_curr_length() << endl;
                        _gameOver = true;
                        break;  
                    }
                    std::vector<Vehicle> *vehicles_list = (Roads[i].get_list_of_lane() + j)->get_list_vehicles();
                    if (vehicles_list->size() != 0)
                    {
                        std::vector<Vehicle>::iterator x;
                        for (x = vehicles_list->begin(); x < vehicles_list->end(); x++)
                        {
                            vehicles->push_back(*x);
                        }
                        float curr_pos_x = vehicles_list->front().get_pos_x();
                        float curr_pos_y = vehicles_list->front().get_pos_y();
                        if (curr_pos_x > 1040 || curr_pos_x < -80 || curr_pos_y > 1040 || curr_pos_y < -80)
                        {
                            (Roads[i].get_list_of_lane() + j)->delVehicle(vehicles_list->begin());
                            _score += vehicles_list->begin()->get_capacity();
                        }
                    }
                }
            }
        }

        if (spawnTime >= spawn_speed * timeStep)
        {
            short int rand0 = std::rand() % 4;
            short int rand1 = std::rand() % 3;
            short int rand2 = std::rand() % 10;
            float spawn_pos_x = (Roads[rand0].get_list_of_lane() + rand1)->get_pos_x();
            float spawn_pos_y = (Roads[rand0].get_list_of_lane() + rand1)->get_pos_y();
            if (rand2 == 0)
            {
                Car p_vehicle = Car(spawn_pos_x, spawn_pos_y, rand0, rand1, 1, carImg_0);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            if (rand2 == 1)
            {
                Car p_vehicle = Car(spawn_pos_x, spawn_pos_y, rand0, rand1, 2, carImg_1);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            if (rand2 == 2)
            {
                Car p_vehicle = Car(spawn_pos_x, spawn_pos_y, rand0, rand1, 3, carImg_2);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            if (rand2 == 3)
            {
                Car p_vehicle = Car(spawn_pos_x, spawn_pos_y, rand0, rand1, 4, carImg_3);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 4)
            {
                Bus p_vehicle = Bus(spawn_pos_x, spawn_pos_y, rand0, rand1, 5, busImg_0);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 5)
            {
                Bus p_vehicle = Bus(spawn_pos_x, spawn_pos_y, rand0, rand1, 6, busImg_1);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 6)
            {
                Bus p_vehicle = Bus(spawn_pos_x, spawn_pos_y, rand0, rand1, 7, busImg_2);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 7)
            {
                Motorbike p_vehicle = Motorbike(spawn_pos_x, spawn_pos_y, rand0, rand1, motorImg_0);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 8)
            {
                Motorbike p_vehicle = Motorbike(spawn_pos_x, spawn_pos_y, rand0, rand1, motorImg_1);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            else if (rand2 == 9)
            {
                Motorbike p_vehicle = Motorbike(spawn_pos_x, spawn_pos_y, rand0, rand1, motorImg_2);
                (Roads[rand0].get_list_of_lane() + rand1)->addVehicle(p_vehicle);
            }
            
            spawnTime -= spawn_speed * timeStep;
        }

        window.clear();
        window.renderBackground(mainBackground);
        window.renderVehicle(vehicles);
        main_score.display(20, 20, window.render());

        for (short int i = 0; i < 4; i++)
        {
            float pos_x = Roads[i].get_trafficlight()->get_pos_x();
            float pos_y = Roads[i].get_trafficlight()->get_pos_y();
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
                cntLight[i].display(pos_x + 6, pos_y - 24, window.render());
            }
            else if (Roads[i].get_trafficlight()->get_curr_color() == "yellow")
            {
                if (_curr_time[i] == 2)
                    Roads[i].get_trafficlight()->ChangeColor(window.render(), "res/gfx/yellow.png", "yellow");

                _curr_time[i] = Roads[i].get_trafficlight()->get_timer();
                Roads[i].get_trafficlight()->set_countdowntime(_curr_time[i]);
                cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {50, 50, 50});

                if (_curr_time[i] == 0)
                {
                    Roads[i].get_trafficlight()->set_color("red");
                    Roads[i].get_trafficlight()->ChangeColor(window.render(), "res/gfx/red.png", "red");
                    Roads[i].get_trafficlight()->set_countdowntime(6);
                    Roads[i].get_trafficlight()->set_timer(6);
                    _curr_time[i] = 6;
                    cntLight[i] = Text(window.render(), "res/dev/Blockletter.otf", 18, to_string(_curr_time[i]), {50, 50, 50});
                }
                cntLight[i].display(pos_x + 6, pos_y - 24, window.render());
            }
            else
            {
                Text nothing = Text(window.render(), "res/dev/Blockletter.otf", 18, "--", {50, 50, 50});
                nothing.display(pos_x + 5, pos_y - 20, window.render());
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
