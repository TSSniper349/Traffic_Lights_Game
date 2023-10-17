#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include<iostream>

class Instruction {
    private:
        SDL_Color m_color;
    public:
        Instruction(const std::string &font_path);
        void Render(SDL_Renderer* renderer, int width, int height);
        void SetColor(SDL_Color color);
};

#endif