#include "Instruction.h"

Instruction::Instruction(TTF_Font* font)
        : m_font(font){

            m_color.r = 0;
            m_color.g = 0;
            m_color.b = 0;
            m_color.a = 255;
        } 

void Instruction::Render(SDL_Renderer* renderer, int width, int height) const {
    // Render instruction window background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect windowRect = { 100, 100, width - 200, height - 200 }; 
    SDL_RenderFillRect(renderer, &windowRect);

    // Render instruction text
    /*SDL_Color textColor = { m_color.r, m_color.g, m_color.b, m_color.a };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, "HAHAHAHAHAHAHAH", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { 150, 150, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Cleanup
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);*/
}

void Instruction::SetColor(SDL_Color color) {
    m_color = color;
}
