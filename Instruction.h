#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Instruction {
    private:
        TTF_Font* m_font;
        SDL_Color m_color;
    public:
        Instruction(TTF_Font* font);
        void Render(SDL_Renderer* renderer, int width, int height) const;
        void SetColor(SDL_Color color);
};

#endif