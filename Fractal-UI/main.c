//
// Created by Lukas Jonkus on 14/05/2025.
//

#include "main.h"
#include "shapes.h"
#include "file_reader.h"

int main(int argc, char* argv[]) {

    struct SDL_Components sdl_components = {
            .window = NULL,
            .renderer = NULL,
    };

    if(initialize_SDL(&sdl_components) == false) {
        destroy_SDL(&sdl_components);
        return 1;
    }

    read_file();
    //run_event_loop(&sdl_components);

    destroy_SDL(&sdl_components);
    return 0;
}

void run_event_loop(struct SDL_Components *sdl_components) {
    // Event loop
    int running = 1;

    int current_rotation = 0;
    int* current_rotation_pointer = &current_rotation;

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    handle_user_input(&event, current_rotation_pointer);
                    break;
            }
        }

        SDL_SetRenderDrawColor(sdl_components->renderer, 0,0,0,255);
        SDL_RenderClear(sdl_components->renderer);

        //create_fractal(sdl_components, current_rotation);

        SDL_RenderPresent(sdl_components->renderer);
    }
}

void handle_user_input(SDL_Event *event, int *rotation_angle) {
    switch (event->key.keysym.sym) {
        case SDLK_w:
            *rotation_angle = (*rotation_angle + 1 + 360) % 360;
            break;
        case SDLK_s:
            *rotation_angle = (*rotation_angle - 1 + 360) % 360;
            break;
        default:
            break;
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




