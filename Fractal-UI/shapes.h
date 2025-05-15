//
// Created by Lukas Jonkus on 14/05/2025.
//

#ifndef FRACTAL_CREATOR_SHAPES_H
#define FRACTAL_CREATOR_SHAPES_H

#include "main.h"

void create_fractal(struct SDL_Components *sdl_components, int rotation_angle);
void calculate_rotation(int angle, float *origin, float *x, float *y);
void add_rotation_to_triangle(int rotation_value, float **x_vertex_values, float **y_vertex_values, float *origin);
void create_triangle(struct SDL_Components *sdl_components,float x_middle, float y_middle, float triangle_size, int branch_number, int rotation_angle);

#endif //FRACTAL_CREATOR_SHAPES_H
