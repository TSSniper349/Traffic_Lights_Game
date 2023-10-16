#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
//#include <tuple>

using namespace std;

class HighScores{
    private:
        SDL_Color m_color;
    public:
        HighScores(const std::string &font_path);
        void Render(SDL_Renderer* renderer, int width, int height) const;
        void SetColor(SDL_Color color);
        //vector<tuple<string, string, int> > readHighScoresFromFile(const string& filename);

};
#endif