#include "HighScores.h"

HighScores::HighScores(const std::string &font_path) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), 32);
    if(!font) {
        std::cout<<"Failed to load font: "<<SDL_GetError()<<std::endl;
    }
    m_color.r = 0;
    m_color.g = 0;
    m_color.b = 0;
    m_color.a = 150;
} 

void HighScores::Render(SDL_Renderer* renderer, int width, int height) const {
    // Render high scores window background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect windowRect = { 100, 100, width - 200, height - 200 }; 
    SDL_RenderFillRect(renderer, &windowRect);
}

void HighScores::SetColor(SDL_Color color) {
    m_color = color;
}

// vector<tuple<string, string, int> > HighScores::readHighScoresFromFile(const string& filename)
// {
//     vector<tuple<string, string, int> > highScores;

//     ifstream file(filename);
//     if (file.is_open())
//     {
//         string line;
//         while (getline(file, line))
//         {
//             istringstream iss(line);
//             string date, name;
//             int score;
//             if (iss >> date >> name >> score)
//             {
//                 highScores.emplace_back(date,name,score);
//             }
//         }
//         file.close();
//     }

//     return highScores;
// }