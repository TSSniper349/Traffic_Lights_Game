#include "TrafficLight.h"
#include "Timer.h"
using namespace std;



TrafficLight::TrafficLight(SDL_Renderer *renderer, short int x, short int y,const string &image_path,int countdown_time): 
_w(30), _h(45), _x(x), _y(y), _curr_color("red"), _countdown_time(countdown_time), check(0) {
    pos.x = x; pos.y = y;
    timer = CountdownTimer(countdown_time);
    auto surface = IMG_Load(image_path.c_str());

    if (!surface){
        cout << "Failed to create surface" << " " << image_path.c_str() <<  endl;
    }
    _TrafficLight_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!_TrafficLight_texture){
        cout << "Failed to create texture" << endl;
    }
}

TrafficLight::TrafficLight() {}

SDL_Texture* TrafficLight::get_texture(){
    return _TrafficLight_texture;
}

void TrafficLight::display(SDL_Renderer *renderer) {
    SDL_Rect rect = {_x, _y, _w, _h};
 //   cout << _x << " " << _y << " " << _w << " " << _h << endl;
    SDL_RenderCopy(renderer,_TrafficLight_texture,nullptr, &rect);
}

string TrafficLight::get_curr_color(){
    return _curr_color;
}

void TrafficLight::set_color(string color){
    _curr_color = color; 
}

void TrafficLight::ChangeColor(SDL_Renderer *renderer,const string &img_path, string color){
    SDL_Surface *surface = IMG_Load(img_path.c_str());
    if (!surface){
        cout << "Failed to create surface" << " " << img_path.c_str() <<  endl;
    }
    SDL_DestroyTexture(_TrafficLight_texture);
    _TrafficLight_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!_TrafficLight_texture){
        cout << "Failed to create texture" << endl;
    }
    _curr_color = color;
    SDL_FreeSurface(surface);
}
int TrafficLight::get_timer(){
    //_countdown_time = timer.check();
    // cout << _countdown_time << endl;
    if (check == 0) {
        timer.Start();
        check = 1;
    }
    return timer.check();
}

void TrafficLight::set_countdowntime(int time){
    _countdown_time = time;
}

int TrafficLight::get_countdown_time(){
    return _countdown_time;
}

void TrafficLight::set_timer(int time){
    _countdown_time = time;
    timer.set_time(time);
    check = 0;
}

Coordination TrafficLight::get_pos(){
    return pos;
}

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

TrafficLight::~TrafficLight(){
    SDL_DestroyTexture(_TrafficLight_texture);
}