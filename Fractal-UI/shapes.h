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


void draw_graphic(struct Graphic graphic);
void centralise_points(struct Coordinates *coordinates);
void create_points_to_draw(struct Coordinates *coordinates);
void flip_points(struct Coordinates *coordinates);

#endif //FRACTAL_CREATOR_SHAPES_H
