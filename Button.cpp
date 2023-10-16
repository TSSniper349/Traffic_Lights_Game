#include "Button.h"

Button::Button(int x, int y, int width, int height, const std::string& text, SDL_Renderer* renderer)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_text(text){

            button_text = Text(renderer, "res/dev/Blockletter.otf", 30, text,{ 0, 255, 255, 255 });
        }

void Button::Render(short int x, short int y, SDL_Renderer* renderer){
    // Render button background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect buttonRect = { m_x, m_y, m_width, m_height };
    SDL_RenderFillRect(renderer, &buttonRect);

    button_text.display(x, y, renderer);
}


bool Button::IsClicked(int mouseX, int mouseY) const {
    return (mouseX >= m_x && mouseX <= m_x + m_width && mouseY >= m_y && mouseY <= m_y + m_height);
}

const std::string &Button::GetText() const
{
    return m_text;
}