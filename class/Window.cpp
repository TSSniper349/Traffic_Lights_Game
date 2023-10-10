#include "Window.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
using namespace std;

SDL_Renderer *Window::renderer = nullptr;

Window::Window(string title, int width, int height): _title(title), _width(width), _height(height) {
    _closed = !init();
}

Window::Window() : Window("", 800, 600) {};
Window::~Window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

bool Window::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        cout << "Failed to initalize SDL" << endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        cout << "Failed to initalize SDL_image" << endl;
        return false;
    }

    if(TTF_Init() == -1){
        cout << "Failed to initalize SDL_TTF" << endl;
        return false;
    }

    _window = SDL_CreateWindow(
            _title.c_str(), 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            _width, _height, 0 
    );

    if (_window == nullptr){
        cout << "Failed to create window" << endl;
        return 0;
    }

    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    
    if (renderer == nullptr){
        cout << "Failed to create render" << endl;
        return 0;
    }

    return true;
}

void Window::pollEvents(){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                _closed = true;
                break;
        
            default:
                break;
        }
    }
}

void Window::clear() const{
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

}