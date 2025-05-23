//
// Created by Lukas Jonkus on 14/05/2025.
//

#ifndef FRACTAL_CREATOR_SHAPES_H
#define FRACTAL_CREATOR_SHAPES_H

#include "main.h"

typedef struct Coordinates {
    float x;
    float y;
} Coordinates, Translation;

typedef struct Transform {
    char *name;
    float rotation;
    struct Coordinates translation;
    float scale;
} Transform;

typedef struct Graphic {
    char *name;
    struct Coordinates *coordinates;
    int num_coordinates;
} Graphic;

typedef struct Graphic_branch {
    Transform *transform;
    Graphic *graphic;
    int start_iteration;
    int end_iteration;
} Graphic_branch;

typedef struct Fractal_branch {
    Transform *transform;
    struct Fractal *fractal;
    int start_iteration;
    int end_iteration;
} Fractal_branch;

typedef struct Fractal {
    char *name;
    Graphic_branch *graphic_branches;
    int num_graphic_branches;

    Fractal_branch *fractal_branches;
    int num_fractal_branches;
} Fractal;


void draw_graphic(Graphic graphic);
void get_instructions();
void store_instructions(int transform_count, int graphic_count, int fractal_count, int *graphic_branch_count, int *fractal_branch_count);
void centralise_points(struct Coordinates *coordinates);
void create_points_to_draw(struct Coordinates *coordinates);
void flip_points(struct Coordinates *coordinates);

#endif //FRACTAL_CREATOR_SHAPES_H
