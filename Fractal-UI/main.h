//
// Created by Lukas Jonkus on 14/05/2025.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#ifndef FRACTAL_CREATOR_MAIN_H
#define FRACTAL_CREATOR_MAIN_H

#define WINDOW_TITLE "Fractal Simulator"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct SDL_Components {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

bool initialize_SDL(struct SDL_Components *sdl_components);
void destroy_SDL(struct SDL_Components *sdl_components);
void run_event_loop(struct SDL_Components *sdl_components);
void handle_user_input(SDL_Event *event, int *rotation_angle);



#endif //FRACTAL_CREATOR_MAIN_H
