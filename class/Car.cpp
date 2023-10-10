#include "Car.h"
#include <iostream>
#include <SDL2/SDL_image.h>
using namespace std;


Car::Car(int w, int h, int x, int y,const string &image_path) : 
_w(w), _h(h), _x(x), _y(y){
    auto surface = IMG_Load(image_path.c_str());

    if (!surface){
        cout << "Failed to create surface" << endl;
    }
    _car_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if(!_car_texture){
        cout << "Failed to create texture" << endl;
    }
}

void Car::draw() const{
    SDL_Rect car = {_x, _y, _w, _h};
    SDL_RenderCopy(Window::renderer,_car_texture,nullptr, &car);
    


}

void Car::move(){
    _x += 1;
    SDL_Delay(10);
}

Car::~Car(){
    SDL_DestroyTexture(_car_texture);
}