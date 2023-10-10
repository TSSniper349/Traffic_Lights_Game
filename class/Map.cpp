#include "Map.h"
#include <iostream>
#include <SDL2/SDL_image.h>
using namespace std;



Map::Map(int w, int h, int x, int y,const string &image_path) : 
_w(w), _h(h), _x(x), _y(y){
    auto surface = IMG_Load(image_path.c_str());

    if (!surface){
        cout << "Failed to create surface" << endl;
    }
    _map_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if(!_map_texture){
        cout << "Failed to create texture" << endl;
    }
}

void Map::draw() const{
    SDL_Rect map = {_x, _y, _w, _h};
    SDL_RenderCopy(Window::renderer,_map_texture,nullptr, &map);
    


}

Map::~Map(){
    SDL_DestroyTexture(_map_texture);
}