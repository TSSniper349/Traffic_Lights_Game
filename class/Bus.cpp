#include "Bus.h"
#include <iostream>
#include <SDL2/SDL_image.h>
using namespace std;


Bus::Bus(int w, int h, int x, int y,const string &image_path) : 
_w(w), _h(h), _x(x), _y(y){
    auto surface = IMG_Load(image_path.c_str());

    if (!surface){
        cout << "Failed to create surface" << endl;
    }
    _bus_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if(!_bus_texture){
        cout << "Failed to create texture" << endl;
    }
}

void Bus::draw() const{
    SDL_Rect bus = {_x, _y, _w, _h};
    SDL_RenderCopy(Window::renderer,_bus_texture,nullptr, &bus);
    


}

void Bus::move(){
    _x += 1;
 //   SDL_Delay(10);
}

Bus::~Bus(){
    SDL_DestroyTexture(_bus_texture);
}