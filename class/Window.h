#ifndef WINDOW
#define WINDOW

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;


class Window{
    private:
        string _title;
        int _width;
        int _height;

        bool init();
        bool _closed;

        SDL_Window *_window = nullptr;
    public:
        static SDL_Renderer *renderer;

    public:
        Window();
        Window(string title, int width, int height);
        void pollEvents();
        void clear() const;
        bool isClosed() const {return _closed;}
        ~Window();

};

#endif