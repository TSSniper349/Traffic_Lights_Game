#ifndef TRAFFICLIGHT
#define TRAFFICLIGHT

#include "Timer.h"
#include "RenderWindow.h"
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class TrafficLight{
    public:
        TrafficLight(SDL_Renderer *renderer, short int x, short int y,const string &image_path, int countdown_time);
        TrafficLight();
        void display(SDL_Renderer *renderer);
        
        int get_countdown_time();
        void set_countdowntime(int time);

        string get_curr_color();
        void set_color(string color);
        void ChangeColor(SDL_Renderer *renderer,const string &img_path, string color);
        void pollEvents();
        SDL_Texture* get_texture();
        ~TrafficLight();

        int get_timer();
        void set_timer(int time);
        // static SDL_Texture *loadFont(const string &message_text);
        // void set_text(const string &message);
        Coordination get_pos();
    
    private:
        string _curr_color;
        CountdownTimer timer;
        int _countdown_time;
        Coordination pos;
        int check;
        int _w, _h;
        int _x, _y;
        SDL_Texture *_TrafficLight_texture = nullptr;
};

#endif