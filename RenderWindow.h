#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Enity.h"
#include"Vehicle.h"
#include"car.h"
#include"text.h"
#include<vector>
#include<iterator>

class RenderWindow {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
    RenderWindow(const char* p_title, short int p_w, short int p_h);
    SDL_Renderer *render();
    SDL_Texture* loadTexture(const char* p_filePath);
    int getRefreshRate();
    void CleanUp();
    void clear();
    void renderBackground(Enity &p_enity);
    void renderVehicle(std::vector<Vehicle> *p_vehicles);
    void renderButton(Enity &p_enity);
    void display();
};
