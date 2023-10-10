#ifndef TRAFFICLIGHT
#define TRAFFICLIGHT

#include "Window.h"
#include "Timer.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <SDL2/SDL.h>
using namespace std;

struct Coor{
    int x, y;
};

class TrafficLight{
    public:
        TrafficLight(int w, int h, int x, int y,const string &image_path, int countdown_time);
        TrafficLight();
        void draw() const;
        
        int get_countdown_time();
        void set_countdowntime(int time);

        string get_curr_color();
        void set_color(string color);
        void ChangeColor(const string &img_path, string color);
        void pollEvents();
        SDL_Texture* get_texture();
        ~TrafficLight();

        int get_timer();
        void set_timer(int time);
        static SDL_Texture *loadFont(const string &message_text);
        void set_text(const string &message);
        Coor get_coor();
    
    private:
        string _curr_color;
        CountdownTimer timer;
        int _countdown_time;
        Coor coor;
        int check;
        int _w, _h;
        int _x, _y;
        SDL_Texture *_TrafficLight_texture = nullptr;
};

#endif
