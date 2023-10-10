#ifndef TEXT
#define TEXT
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
using namespace std;



class Text{
    public: 
        Text(SDL_Renderer *renderer, const char *message);
        ~Text();

        void display(int x, int y, SDL_Renderer *renderer, const char *message) const;

        static SDL_Texture *loadFont(SDL_Renderer *renderer, const char *message);
    private:
        mutable SDL_Texture *_text_texture = nullptr;   
        mutable SDL_Rect _text_rect;

};

#endif