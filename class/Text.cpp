#include "Text.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Window.h"
using namespace std;


Text::Text(SDL_Renderer *renderer,
    const char *message) {

    _text_texture = loadFont(renderer, message);
    SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);

}

void Text::display(int x, int y, SDL_Renderer *renderer, const char *message) const{
    _text_rect.x = x;
    _text_rect.y = y;
    SDL_DestroyTexture(_text_texture);
    _text_texture = loadFont(renderer, message);
    // if(!_text_texture){
    //     SDL_DestroyTexture(_text_texture);
    //     cout << "Failed to create texture" << endl;
    // }
    SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
    SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
}

SDL_Texture *Text::loadFont(SDL_Renderer *renderer,const char *message){
    TTF_Font *font = TTF_OpenFont("class/fonts/arial.ttf", 24);
    SDL_Color color = {255, 255, 255, 255}; // white color
    

    if (!font){
         cout << "Failed to create font" << " " << TTF_GetError() << endl;
    }

    // Render the text to a surface, then create a texture from the surface
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(Window::renderer, text_surface);

    if(!text_surface){
        // SDL_DestroyTexture(text_texture);
        // SDL_FreeSurface(text_surface);
        // text_surface = TTF_RenderText_Solid(font, message, color);
        // text_texture = SDL_CreateTextureFromSurface(Window::renderer, text_surface);
        cout << "Failed to create surface" << " " << SDL_GetError() << endl;
    }

    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    return text_texture; 
}
  
Text::~Text(){
    SDL_DestroyTexture(_text_texture);
}