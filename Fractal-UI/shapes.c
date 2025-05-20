//
// Created by Lukas Jonkus on 14/05/2025.
//

#include "shapes.h"
#include "main.h"

void create_fractal(struct SDL_Components *sdl_components, int rotation_angle) {
    float start_x = SCREEN_WIDTH/2;
    float start_y = SCREEN_HEIGHT/2;

    create_triangle(sdl_components, start_x, start_y, 50, 3, rotation_angle);
}

void add_rotation_to_triangle(int rotation_value, float **x_vertex_values, float **y_vertex_values, float *origin) {
    for (int i = 0; i < 3; i++) {
        calculate_rotation(rotation_value, origin, x_vertex_values[i], y_vertex_values[i]);
    }
}

void calculate_rotation(int angle, float *origin, float *x, float *y) {
    //x' = (x - h)cos(θ) - (y - k)sin(θ) + h
    //y' = (x - h)sin(θ) + (y - k)cos(θ) + k
    float h = origin[0];
    float k = origin[1];

    float x0 = *x;
    float y0 = *y;

    float new_x = (x0 - h) * cos(angle) - (y0 - k) * sin(angle) + h;
    float new_y = (x0 - h) * sin(angle) + (y0 - k) * cos(angle) + k;

    *x = new_x;
    *y = new_y;
}

/**
 * Function to create a triangle using lines
 *
 * @param sdl_components allow the function to draw the triangle
 * @param x_middle x midpoint of the triangle
 * @param y_middle y midpoint of the triangle
 * @param triangle_size size of each edge
 */
void create_triangle(struct SDL_Components *sdl_components,float x_middle, float y_middle, float triangle_size, int branch_number, int rotation_angle) {
    branch_number--;
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

    float *x_vertex_values[3] = {&vertex_1_x, &vertex_2_x, &vertex_3_x};
    float *y_vertex_values[3] = {&vertex_1_y, &vertex_2_y, &vertex_3_y};
    float origin[2] = {x_middle, y_middle};

    printf("%i\n", rotation_angle);

    add_rotation_to_triangle(rotation_angle, x_vertex_values, y_vertex_values, origin);

    SDL_SetRenderDrawColor(sdl_components->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_1_x, vertex_1_y, vertex_2_x, vertex_2_y);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_2_x, vertex_2_y, vertex_3_x, vertex_3_y);
    SDL_RenderDrawLine(sdl_components->renderer, vertex_3_x, vertex_3_y, vertex_1_x, vertex_1_y);

//    SDL_RenderDrawLine(sdl_components->renderer, x_middle, y_middle, vertex_2_x, vertex_2_y);
//    SDL_RenderDrawLine(sdl_components->renderer, x_middle, y_middle, vertex_3_x, vertex_3_y);
//    SDL_RenderDrawLine(sdl_components->renderer, x_middle, y_middle, vertex_1_x, vertex_1_y);

    if(branch_number > 0) {
        create_triangle(sdl_components, vertex_1_x, vertex_1_y, 50, branch_number, rotation_angle);
        create_triangle(sdl_components, vertex_2_x, vertex_2_y, 50, branch_number, rotation_angle);
        create_triangle(sdl_components, vertex_3_x, vertex_3_y, 50, branch_number, rotation_angle);
    }

    //Length of each side for debugging purposes
//    float len1 = sqrt(((vertex_1_x - vertex_2_x) * (vertex_1_x - vertex_2_x)) + ((vertex_1_y - vertex_2_y) * (vertex_1_y - vertex_2_y)));
//    float len2 = sqrt(((vertex_3_x - vertex_2_x) * (vertex_3_x - vertex_2_x)) + ((vertex_3_y - vertex_2_y) * (vertex_3_y - vertex_2_y)));
//    float len3 = sqrt(((vertex_1_x - vertex_3_x) * (vertex_1_x - vertex_3_x)) + ((vertex_1_y - vertex_3_y) * (vertex_1_y - vertex_3_y)));
//    printf("%.2f, %.2f, %.2f\n", len1, len2, len3);
}

void draw_graphic(struct Graphic graphic, struct SDL_Components *sdl_components) {
    SDL_SetRenderDrawColor(sdl_components->renderer, 255, 255, 255, 255);
    struct Coordinates coordinate1, coordinate2;
    for (int i = 0; i < graphic.num_coordinates; i++) {
        if(i+1 != graphic.num_coordinates) {
            coordinate1 = graphic.coordinates[i];
            coordinate2 = graphic.coordinates[i+1];
            create_points_to_draw(&coordinate1);
            create_points_to_draw(&coordinate2);
            SDL_RenderDrawLine(sdl_components->renderer, coordinate1.x, coordinate1.y, coordinate2.x, coordinate2.y);
        }
    }
}

void create_points_to_draw(struct Coordinates *coordinates) {
    //flip_points(coordinates);
    centralise_points(coordinates);
}

void flip_points(struct Coordinates *coordinates) {
    coordinates->x = coordinates->x * -1;
    coordinates->y = coordinates->y * -1;
}

void centralise_points(struct Coordinates *coordinates) {
    coordinates->x = coordinates->x + SCREEN_WIDTH/2;
    coordinates->y = coordinates->y + SCREEN_HEIGHT/2;
}