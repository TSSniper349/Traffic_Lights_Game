#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char **argv) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Create a window and renderer
    SDL_Window *window = SDL_CreateWindow("SDL2 Text Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load a font
    TTF_Font *font = TTF_OpenFont("class/fonts/arial.ttf", 24);
    SDL_Color color = {255, 255, 255, 255}; // white color

    // Render the text to a surface, then create a texture from the surface
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello, SDL2!", color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Clean up the surface
    SDL_FreeSurface(surface);

    // Main loop
    int quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the window
        SDL_RenderClear(renderer);

        // Render the text
        SDL_Rect destRect = {100, 100, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &destRect);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
