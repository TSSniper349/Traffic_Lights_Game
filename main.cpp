#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <vector>
#include <string>
#include "Init.h"
#include "Button.h"
#include "Instruction.h"
#include "HighScores.h"
#include "text.h"


using namespace std;


const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 960;

int main() {

     // Initialize SDL
    if (!init())
    {
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer creation failed. SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load background image
    SDL_Texture* Background = loadTexture("/Resource/Photos/background.jpg", renderer);
    if (Background == nullptr)
    {
        return 1;
    }

    // Load font
    TTF_Font* Rg_font = TTF_OpenFont("/Resource/Aller/Aller_Rg.ttf", 32); 
    if (Rg_font == nullptr) {
        std::cout << "Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    Text gameTitle(renderer, "/Resource/Aller/Aller_Bd.ttf", 72, "TRAFFIC LIGHTS GAME", { 0, 0, 0, 0}, "Normal");

    Text highscoresTitle(renderer, "/Resource/Aller/Aller_Bd.ttf", 72, "HIGH SCORES", { 0, 0, 255, 0}, "Normal");
    Text Date(renderer, "/Resource/Aller/Aller_Rg.ttf", 40, "Date", { 0, 0, 0, 255}, "Normal");
    Text Player(renderer, "/Resource/Aller/Aller_Rg.ttf", 40, "Player", { 0, 0, 0, 255}, "Normal");
    Text Score(renderer, "/Resource/Aller/Aller_Rg.ttf", 40, "Score", { 0, 0, 0, 255}, "Normal");



    Text instructionTitle(renderer, "/Resource/Aller/Aller_Bd.ttf", 72, "INSTRUCTION", { 0, 0, 255, 0}, "Normal");
    std::string instructionText = "Objective:\n - To control the traffic lights and manage the flow of traffic to avoid accidents and ensure smooth traffic movement.\n\nControl:\n - Use the W, A, S, D key to control the traffic light at\nthe top, left, bottom, right lane respectively.\n\nScoring:\n - Motorbikes give 1 pt, cars give 1-4 pts based on\nthe vehicle's color and buses give 5-7 pts.\n\n Conditions:\n - The player loses the game if a vehicle touches the edge of the window.";
    Text instruction(renderer, "/Resource/Aller/Aller_Rg.ttf", 32, instructionText, { 0, 0, 255, 0}, "Instruction");


    // Create buttons
    std::vector<Button> buttons;
    buttons.emplace_back(SCREEN_WIDTH / 2 - 100, 300, 200, 50, "START", renderer);
    buttons.emplace_back(SCREEN_WIDTH / 2 - 100, 400, 200, 50, "HIGH SCORES", renderer);
    buttons.emplace_back(SCREEN_WIDTH / 2 - 100, 500, 200, 50, "INSTRUCTION", renderer);
    buttons.emplace_back(SCREEN_WIDTH / 2 - 100, 600, 200, 50, "EXIT", renderer);
    int button_height = 310;

    // Instruction window
    Instruction instructionWindow(Rg_font);

    //High scores window 
    HighScores highscoresWindow(Rg_font);


    //read high score from file
    vector<tuple<string, string, int> > highScores = highscoresWindow.readHighScoresFromFile("data.txt");
    

    // Main loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // Event handling
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Handle button clicks
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                for (const Button& button : buttons) {
                    if (button.IsClicked(mouseX, mouseY)) {
                        
                        if (button.GetText() == "EXIT") {
                            quit = true;
                        }
                        else if (button.GetText() == "INSTRUCTION") {
                            // Render instruction window
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            instructionWindow.Render(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                            SDL_RenderPresent(renderer);

                            // Render background image
                            SDL_RenderClear(renderer);
                            renderTexture(Background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                            // Render the instruction title text
                            instructionTitle.display(250, 150, renderer);

                            // Render the white box with curved corners
                            Sint16 x_box = 80;
                            Sint16 y_box = 250;
                            Sint16 w_box = 800;
                            Sint16 h_box = 800;
                            Sint16 radius_box = 20;
                            roundedBoxRGBA(renderer, x_box, y_box, x_box + w_box, y_box + h_box, radius_box, 255, 255, 255, 200);

                            // Render text
                            instruction.display(100, 250, renderer);

                            SDL_RenderPresent(renderer);

                            // Wait for a key press to exit the instruction window
                            bool instructionWindowOpen = true;
                            while (instructionWindowOpen) {
                                while (SDL_PollEvent(&e) != 0 && e.key.keysym.sym == SDLK_ESCAPE) {
                                    if (e.type == SDL_QUIT) {
                                        quit = true;
                                        instructionWindowOpen = false;
                                    }
                                    else if (e.type == SDL_KEYDOWN) {
                                        instructionWindowOpen = false;
                                    }
                                }
                            }

                            // Render main menu again
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            // Render buttons
                            buttons[0].Render(435, 305,renderer);
                            buttons[1].Render(385, 405,renderer);
                            buttons[2].Render(385, 505,renderer);
                            buttons[3].Render(450, 605,renderer);   
                            SDL_RenderPresent(renderer);
                        }

                        else if (button.GetText() == "HIGH SCORES") {
                            // Render high scores window
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            highscoresWindow.Render(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                            SDL_RenderPresent(renderer);

                            // Render background image
                            SDL_RenderClear(renderer);
                            renderTexture(Background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                            // Render the high scores title text
                            highscoresTitle.display(250, 150, renderer);

                            // Render the white box with curved corners
                            Sint16 x_box = 80;
                            Sint16 y_box = 250;
                            Sint16 w_box = 800;
                            Sint16 h_box = 600;
                            Sint16 radius_box = 20;
                            roundedBoxRGBA(renderer, x_box, y_box, x_box + w_box, y_box + h_box, radius_box, 255, 255, 255, 200);

                            Date.display(100, 250, renderer);
                            Player.display(400, 250, renderer);
                            Score.display(700, 250, renderer);

                            // Render the high scores
                            int highscore_height = 300;
                            for (const auto& score : highScores)
                            {
                                std::string date = std::get<0>(score);
                                std::string player = std::get<1>(score);
                                int scoreValue = std::get<2>(score);
                                std::string score_str = to_string(scoreValue);

                                Text date_data(renderer, "/Resource/Aller/Aller_Rg.ttf", 40, date.c_str(), { 0, 0, 0, 255}, "Normal");
                                Text player_data(renderer, "/Resource/Aller/Aller_Rg.ttf", 40, player.c_str(), { 0, 0, 0, 255}, "Normal");
                                Text score_data(renderer, "/Resource/Aller/Aller_Rg.ttf", 40, score_str.c_str(), { 0, 0, 0, 255}, "Normal");

                                date_data.display(100, highscore_height, renderer);
                                player_data.display(400, highscore_height, renderer);
                                score_data.display(700, highscore_height, renderer);

                                highscore_height += 50;
                            }
                            SDL_RenderPresent(renderer);

                            // Wait for a key press to exit the highscore window
                            bool highscoresWindowOpen = true;
                            while (highscoresWindowOpen) {
                                while (SDL_PollEvent(&e) != 0 && e.key.keysym.sym == SDLK_ESCAPE) {
                                    if (e.type == SDL_QUIT) {
                                        quit = true;
                                        highscoresWindowOpen = false;
                                    }
                                    else if (e.type == SDL_KEYDOWN) {
                                        highscoresWindowOpen = false;
                                    }
                                }
                            }

                            // Render main menu again
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            // Render buttons
                            buttons[0].Render(435, 305,renderer);
                            buttons[1].Render(385, 405,renderer);
                            buttons[2].Render(385, 505,renderer);
                            buttons[3].Render(450, 605,renderer);
                            SDL_RenderPresent(renderer);
                        }
                        break;
                    }
                }
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render menu background
        renderTexture(Background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Render the title text
        gameTitle.display(125, 150, renderer);

        // Render buttons
        buttons[0].Render(435, 305,renderer);
        buttons[1].Render(385, 405,renderer);
        buttons[2].Render(385, 505,renderer);
        buttons[3].Render(450, 605,renderer);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

