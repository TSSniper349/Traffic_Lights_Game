#include"RenderWindow.h"
#include"Lane.h"
#include<iostream>

// initialize a new window and a new renderer
RenderWindow::RenderWindow(const char* p_title, short int p_w, short int p_h): window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        std::cout<<"Window failed to init. Error: "<<SDL_GetError()<<std::endl;
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

}

// return the pointer to the renderer
SDL_Renderer* RenderWindow::render() {
    return renderer;
}

// load and return a texture on the window
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture==NULL) {
        std::cout<<"Failed to load Texture. Error: "<<SDL_GetError()<<std::endl;
    }

    return texture;
}

// return refresh rate of the window
int RenderWindow::getRefreshRate() {

    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);
    
    return mode.refresh_rate;
}

// destroy the window and renderer
void RenderWindow::CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

// clear the renderer
void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

// render the background
void RenderWindow::renderBackground(Enity &p_enity) {
    SDL_Rect dst;
    dst.x = p_enity.get_pos_x();
    dst.y = p_enity.get_pos_y();
    dst.w = p_enity.get_frame().w;
    dst.h = p_enity.get_frame().h;

    SDL_RenderCopy(renderer, p_enity.get_tex(), NULL, &dst);
}

// render the button
void RenderWindow::renderButton(Enity &p_enity) {
    SDL_Rect dst;
    dst.x = p_enity.get_pos_x();
    dst.y = p_enity.get_pos_y();
    dst.w = 130;
    dst.h = 40;

    SDL_RenderCopy(renderer, p_enity.get_tex(), NULL, &dst);
}

// iterates over a vector of Vehicle objects and renders each vehicle
void RenderWindow::renderVehicle(std::vector<Vehicle> *p_vehicles) {
    std::vector<Vehicle>::iterator i;
    for(i = p_vehicles->begin(); i < p_vehicles->end(); i++) {

        SDL_Rect src;
        src.x = i->get_frame().x;
        src.y = i->get_frame().y;
        src.w = 1500;
        src.h = 2000;
        SDL_Rect dst;
        dst.x = i->get_pos_x();
        dst.y = i->get_pos_y();
        dst.w = i->get_frame().w;
        dst.h = i->get_frame().h;
        SDL_Point center;
        center.x = 0;
        center.y = 0;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer, i->get_tex(), &src, &dst, i->get_angle(), &center, flip);
    }
}

// update the window by presenting the rendered content
void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}