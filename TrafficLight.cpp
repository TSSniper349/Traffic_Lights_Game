#include "TrafficLight.h"
#include "Timer.h"
using namespace std;


// initialize a traffic light with a specified coordinates, an image of the light and its countdown time
TrafficLight::TrafficLight(SDL_Renderer *renderer, short int x, short int y,const string &image_path,int countdown_time): 
_curr_color("red"), _countdown_time(countdown_time), check(0) {
    Enity::set_pos_x(x);
    Enity::set_pos_y(y);
    Enity::set_frame(33,88);
    timer = CountdownTimer(countdown_time);
    auto surface = IMG_Load(image_path.c_str());

    tex = SDL_CreateTextureFromSurface(renderer, surface);
    
}

TrafficLight::TrafficLight() {}

// display the traffic lights on the screen
void TrafficLight::display(SDL_Renderer *renderer) {
    SDL_Rect dst;
    dst.x = pos_x;
    dst.y = pos_y;
    dst.w = frame.w/1.4;
    dst.h = frame.h/1.4;
    SDL_RenderCopy(renderer,tex,&frame,&dst);
}

// set the current color of the traffic light
string TrafficLight::get_curr_color(){
    return _curr_color;
}

// return the current color of the traffic light
void TrafficLight::set_color(string color){
    _curr_color = color; 
}

// change the color of the light to another color
void TrafficLight::ChangeColor(SDL_Renderer *renderer,const string &img_path, string color){
    SDL_Surface *surface = IMG_Load(img_path.c_str());
    SDL_DestroyTexture(tex);
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    _curr_color = color;
    SDL_FreeSurface(surface);
}

//  returns the remaining time on the countdown timer. It starts the timer if check is 0.
int TrafficLight::get_timer(){
    if (check == 0) {
        timer.Start();
        check = 1;
    }
    return timer.check();
}

// set the countdown time of the traffic light
void TrafficLight::set_countdowntime(int time){
    _countdown_time = time;
}

// return the countdown time of the traffic light
int TrafficLight::get_countdown_time(){
    return _countdown_time;
}

// set the countdown time and reset the timer
void TrafficLight::set_timer(int time){
    _countdown_time = time;
    timer.set_time(time);
    check = 0;
}

// check for a key press event and updates the current color of the traffic light based on the pressed key
void TrafficLight::pollEvents(){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_a:
                    _curr_color = "green";
                    break;
                default:
                    break;
            }
        }
    }
}

// destroy traffic light texture
TrafficLight::~TrafficLight(){
    SDL_DestroyTexture(tex);
}