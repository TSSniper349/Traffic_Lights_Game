#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "text.h"

// represent buttons on the main menu screen
class Button {
public:
    Button(int x, int y, int width, int height, const std::string& text, SDL_Renderer* renderer);
    void Render(short int x, short int y, SDL_Renderer* renderer);
    bool IsClicked(int mouseX, int mouseY) const;
    const std::string& GetText() const;

private:
    int m_x;// the x-coordinate of the button
    int m_y;// the y-coordinate of the buttom
    int m_width;// the width of the button
    int m_height;;// the height of the button
    std::string m_text;// the message of the button
    Text button_text;// the text of the button
};

#endif