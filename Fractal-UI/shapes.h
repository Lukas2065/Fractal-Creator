//
// Created by Lukas Jonkus on 14/05/2025.
//

#ifndef FRACTAL_CREATOR_SHAPES_H
#define FRACTAL_CREATOR_SHAPES_H

#include "main.h"

void create_fractal(struct SDL_Components *sdl_components);
float add_rotation(float rotation_value,float coordinate_value);
float add_displacement(float displacement_value,float coordinate_value);
void create_triangle(struct SDL_Components *sdl_components,float x_middle, float y_middle, float triangle_size);

#endif //FRACTAL_CREATOR_SHAPES_H
