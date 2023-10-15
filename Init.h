#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

bool init();
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int width, int height );

#endif