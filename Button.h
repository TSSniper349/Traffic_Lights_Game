#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "text.h"

class Button {
public:
    Button(int x, int y, int width, int height, const std::string& text, SDL_Renderer* renderer);
    void Render(short int x, short int y, SDL_Renderer* renderer);
    bool IsClicked(int mouseX, int mouseY) const;
    const std::string& GetText() const;

    
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    std::string m_text;
    Text button_text;
};

#endif