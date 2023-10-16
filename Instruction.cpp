#include "Instruction.h"

Instruction::Instruction(const std::string &font_path) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), 32);
    if(!font) {
        std::cout<<"Failed to load font: "<<SDL_GetError()<<std::endl;
    }
    m_color.r = 0;
    m_color.g = 0;
    m_color.b = 0;
    m_color.a = 150;
} 

void Instruction::Render(SDL_Renderer* renderer, int width, int height) const {
    // Render instruction window background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect windowRect = { 100, 100, width - 200, height - 200 }; 
    SDL_RenderFillRect(renderer, &windowRect);
}

void Instruction::SetColor(SDL_Color color) {
    m_color = color;
}