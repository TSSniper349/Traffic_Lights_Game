#pragma once
#include <SDL2/SDL_ttf.h>
#include<SDL2/SDL.h>
#include<iostream>

class Text {
    private:
        SDL_Texture *tex;
        SDL_Rect rect;
    public:
        Text();
        Text(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color, std::string type);
        void display(short int x, short int y, SDL_Renderer *renderer);
        static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color);
        static SDL_Texture *loadFontInstruction(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color, int screen_width);
};