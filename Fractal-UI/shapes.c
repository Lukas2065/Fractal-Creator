//
// Created by Lukas Jonkus on 14/05/2025.
//

#include "shapes.h"
#include "main.h"

void create_fractal(struct SDL_Components *sdl_components) {
    float start_x = SCREEN_WIDTH/2;
    float start_y = SCREEN_HEIGHT/2;

    int branches = 5;

    for (int i=0;i<branches;i++) {
        create_triangle(sdl_components, start_x, start_y, 50);

    }
}

float add_rotation(float rotation_value, float coordinate_value) {

}

float add_displacement(float displacement_value, float coordinate_value) {

}

/**
 * Function to create a triangle using lines
 *
 * @param sdl_components allow the function to draw the triangle
 * @param x_middle x midpoint of the triangle
 * @param y_middle y midpoint of the triangle
 * @param triangle_size size of each edge
 */
void create_triangle(struct SDL_Components *sdl_components,float x_middle, float y_middle, float triangle_size) {
    float radius = triangle_size / sqrt(3);

    float angle1 = 0;
    float angle2 = 2.0f * M_PI / 3.0f;
    float angle3 = 4.0f * M_PI / 3.0f;

    float vertex_1_x = x_middle + radius * cos(angle1);
    float vertex_1_y = y_middle + radius * sin(angle1);

    float vertex_2_x = x_middle + radius * cos(angle2);
    float vertex_2_y = y_middle + radius * sin(angle2);

    float vertex_3_x = x_middle + radius * cos(angle3);
    float vertex_3_y = y_middle + radius * sin(angle3);

    SDL_SetRenderDrawColor(sdl_components->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_1_x, vertex_1_y, vertex_2_x, vertex_2_y);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_2_x, vertex_2_y, vertex_3_x, vertex_3_y);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_3_x, vertex_3_y, vertex_1_x, vertex_1_y);

    SDL_RenderDrawLine(sdl_components->renderer, x_middle, y_middle, vertex_2_x, vertex_2_y);
    SDL_RenderDrawLine(sdl_components->renderer, x_middle, y_middle, vertex_3_x, vertex_3_y);
    SDL_RenderDrawLine(sdl_components->renderer, x_middle, y_middle, vertex_1_x, vertex_1_y);

    //Length of each side for debugging purposes
//    float len1 = sqrt(((vertex_1_x - vertex_2_x) * (vertex_1_x - vertex_2_x)) + ((vertex_1_y - vertex_2_y) * (vertex_1_y - vertex_2_y)));
//    float len2 = sqrt(((vertex_3_x - vertex_2_x) * (vertex_3_x - vertex_2_x)) + ((vertex_3_y - vertex_2_y) * (vertex_3_y - vertex_2_y)));
//    float len3 = sqrt(((vertex_1_x - vertex_3_x) * (vertex_1_x - vertex_3_x)) + ((vertex_1_y - vertex_3_y) * (vertex_1_y - vertex_3_y)));
//    printf("%.2f, %.2f, %.2f\n", len1, len2, len3);
}