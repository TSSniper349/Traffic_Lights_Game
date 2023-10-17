#pragma once
#include <SDL2/SDL_ttf.h>
#include<SDL2/SDL.h>
#include<iostream>

// represent text to be rendered on the screen using SDL
class Text {
    private:
        SDL_Texture *tex;//pointer to a texure of the text
        SDL_Rect rect;// the frame of the text
    public:
        Text();
        Text(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color);
        Text(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color,std::string type);
        void display(short int x, short int y, SDL_Renderer *renderer);
        static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color);
        static SDL_Texture *loadFontInstruction(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color, int screen_width);
};