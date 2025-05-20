//
// Created by Lukas Jonkus on 14/05/2025.
//

#ifndef FRACTAL_CREATOR_SHAPES_H
#define FRACTAL_CREATOR_SHAPES_H

#include "main.h"

struct Coordinates {
    float x;
    float y;
};

struct Transform {
    char *name;
    float rotation;
    struct Coordinates translation;
    float scale;
};

struct Graphic {
    char *name;
    struct Coordinates *coordinates;
    int num_coordinates;
};

struct Graphic_branch {
    struct Transform *transform;
    struct Graphic *graphic;
};

struct Fractal_branch {
    struct Transform *transform;
    struct Fractal *fractal;
};

struct Fractal {
    char *name;
    struct Graphic_branch *graphic_branches;
    int num_graphic_branches;

    struct Fractal_branch *fractal_branches;
    int num_fractal_branches;
};


void draw_graphic(struct Graphic graphic, struct SDL_Components *sdl_components);
void create_fractal(struct SDL_Components *sdl_components, int rotation_angle);
void calculate_rotation(int angle, float *origin, float *x, float *y);
void add_rotation_to_triangle(int rotation_value, float **x_vertex_values, float **y_vertex_values, float *origin);
void create_triangle(struct SDL_Components *sdl_components,float x_middle, float y_middle, float triangle_size, int branch_number, int rotation_angle);
void centralise_points(struct Coordinates *coordinates);
void create_points_to_draw(struct Coordinates *coordinates);
void flip_points(struct Coordinates *coordinates);

#endif //FRACTAL_CREATOR_SHAPES_H
