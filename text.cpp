#include"text.h"
#include"RenderWindow.h"

Text::Text() {}

Text::Text(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color) {
    tex = loadFont(renderer, font_path, font_size, message_text, color);
    SDL_QueryTexture(tex, nullptr, nullptr, &rect.w, &rect.h);
}

Text::Text(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color, std::string type) {
    tex = loadFontInstruction(renderer, font_path, font_size, message_text, color, 960);
    SDL_QueryTexture(tex, nullptr, nullptr, &rect.w, &rect.h);
}
    
void Text::display(short int x, short int y, SDL_Renderer *renderer) {
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(renderer, tex, nullptr, &rect);
}

SDL_Texture *Text::loadFont(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if(!font) {
        std::cout<<"Failed to load font: "<<SDL_GetError()<<std::endl;
    }

    SDL_Surface *text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
    if(!text_surface) {
        std::cout<<"Failed to load text surface"<<std::endl;
    }

    auto text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
    if(!text_texture) {
        std::cout<<"Failed to load text texture"<<std::endl;
    }
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    return text_texture;
}

SDL_Texture *Text::loadFontInstruction(SDL_Renderer *renderer, const std::string &font_path, short int font_size, const std::string &message_text, const SDL_Color &color, int screen_width) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if(!font) {
        std::cout<<"Failed to load font: "<<SDL_GetError()<<std::endl;
    }

    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(font, message_text.c_str(), color, screen_width - 100);
    if(!text_surface) {
        std::cout<<"Failed to load text surface"<<std::endl;
    }

    auto text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
    if(!text_texture) {
        std::cout<<"Failed to load text texture"<<std::endl;
    }
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    return text_texture;
}