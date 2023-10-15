#include"RenderWindow.h"
#include"Lane.h"
#include<iostream>

RenderWindow::RenderWindow(const char* p_title, short int p_w, short int p_h): window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        std::cout<<"Window failed to init. Error: "<<SDL_GetError()<<std::endl;
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
}

SDL_Renderer* RenderWindow::render() {
    return renderer;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture==NULL) {
        std::cout<<"Failed to load Texture. Error: "<<SDL_GetError()<<std::endl;
    }

    return texture;
}

int RenderWindow::getRefreshRate() {

    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);
    
    return mode.refresh_rate;
}

void RenderWindow::CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::renderBackground(Enity &p_enity) {
    SDL_Rect dst;
    dst.x = p_enity.get_pos().x;
    dst.y = p_enity.get_pos().y;
    dst.w = p_enity.get_frame().w;
    dst.h = p_enity.get_frame().h;

    SDL_RenderCopy(renderer, p_enity.get_tex(), NULL, &dst);
}

void RenderWindow::renderVehicle(std::vector<Vehicle> *p_vehicles) {
    std::vector<Vehicle>::iterator i;
    for(i = p_vehicles->begin(); i < p_vehicles->end(); i++) {

        SDL_Rect src;
        src.x = i->get_frame().x;
        src.y = i->get_frame().y;
        src.w = 1500;
        src.h = 2000;
        SDL_Rect dst;
        dst.x = i->get_pos().x;
        dst.y = i->get_pos().y;
        dst.w = i->get_frame().w;
        dst.h = i->get_frame().h;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer, i->get_tex(), &src, &dst, i->get_angle(), &i->get_center(), flip);
    }
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}