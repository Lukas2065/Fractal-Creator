//
// Created by Lukas Jonkus on 14/05/2025.
//

#include "main.h"
#include "shapes.h"

int main(int argc, char* argv[]) {

    struct SDL_Components sdl_components = {
            .window = NULL,
            .renderer = NULL,
    };

    if(initialize_SDL(&sdl_components) == false) {
        destroy_SDL(&sdl_components);
        return 1;
    }

    run_event_loop(&sdl_components);

    destroy_SDL(&sdl_components);
    return 0;
}

void run_event_loop(struct SDL_Components *sdl_components) {
    // Event loop
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(sdl_components->renderer, 0,0,0,255);
        SDL_RenderClear(sdl_components->renderer);

        create_fractal(sdl_components);

        SDL_RenderPresent(sdl_components->renderer);
    }
}

bool initialize_SDL(struct SDL_Components *sdl_components) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    sdl_components->window = window;
    sdl_components->renderer = renderer;
    return true;
}

void destroy_SDL(struct SDL_Components *sdl_components) {
    // Clean up
    SDL_DestroyWindow(sdl_components->window);
    SDL_DestroyRenderer(sdl_components->renderer);
    SDL_Quit();
}




