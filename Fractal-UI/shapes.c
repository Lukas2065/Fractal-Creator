//
// Created by Lukas Jonkus on 14/05/2025.
//

#include "shapes.h"
#include "main.h"

/**
 * Function to create a triangle using lines
 *
 * @param sdl_components
 * @param triangle_size how far the triangle is from the middle of itself
 */
void createTriangle(struct SDL_Components *sdl_components,float triangle_size) {
    float x_middle = SCREEN_WIDTH/2;
    float y_middle = SCREEN_HEIGHT/2;

    float adjacent_length = triangle_size/2;
    float opposite_length = adjacent_length * tan(30);
    float hypotenuse_length = adjacent_length / cos(30);

    printf("hypotenuse_length: %.2f\nopposite_length: %.2f\nadjacent_length: %.2f\n", hypotenuse_length, opposite_length,adjacent_length);

    float vertex_1_x = x_middle + adjacent_length;
    float vertex_1_y = y_middle + hypotenuse_length;

    float vertex_2_x = x_middle - adjacent_length;
    float vertex_2_y = y_middle + hypotenuse_length;

    float vertex_3_x = x_middle;
    float vertex_3_y = y_middle - hypotenuse_length;

    printf("Vertex 1: %.2f, %.2f\nVertex 2: %.2f, %.2f\nVertex 3: %.2f, %.2f\n",
           vertex_1_x, vertex_1_y,
           vertex_2_x, vertex_2_y,
           vertex_3_x, vertex_3_y);

    SDL_SetRenderDrawColor(sdl_components->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_1_x, vertex_1_y, vertex_2_x, vertex_2_y);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_2_x, vertex_2_y, vertex_3_x, vertex_3_y);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_3_x, vertex_3_y, vertex_1_x, vertex_1_y);

    SDL_SetRenderDrawColor(sdl_components->renderer, 0, 255, 255, 255);
    SDL_Rect rect1 = { vertex_1_x, vertex_1_y, 2, 2};
    SDL_RenderDrawRect(sdl_components->renderer, &rect1);

    SDL_SetRenderDrawColor(sdl_components->renderer, 255, 0, 255, 255);
    SDL_Rect rect2 = { vertex_2_x, vertex_2_y, 2, 2};
    SDL_RenderDrawRect(sdl_components->renderer, &rect2);

    SDL_SetRenderDrawColor(sdl_components->renderer, 0, 0, 255, 255);
    SDL_Rect rect3 = { vertex_3_x, vertex_3_y, 2, 2};
    SDL_RenderDrawRect(sdl_components->renderer, &rect3);

    SDL_SetRenderDrawColor(sdl_components->renderer, 255, 100, 255, 255);
    SDL_Rect middle = { x_middle, y_middle, 4, 4};
    SDL_RenderDrawRect(sdl_components->renderer, &middle);
}
