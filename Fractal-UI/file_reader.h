//
// Created by Lukas Jonkus on 16/05/2025.
//

#include "main.h"
#include "shapes.h"
#include "svg_handler.h"

#ifndef FRACTAL_CREATOR_FILE_READER_H
#define FRACTAL_CREATOR_FILE_READER_H

int get_num_coordinates(char *line);
void get_coordinates(char *string_coordinates, struct Coordinates *coordinates);
Graphic store_graphic_information(char *line);
Transform store_transform_information(char *line);
void store_fractal_information(Fractal *current_fractal, char *line);
void store_branch_information(Fractal *current_fractal, Transform *transforms, Graphic *graphics, Fractal *fractals, int transform_count, int graphic_count, int fractal_count, int *current_graphic_branch, int *current_fractal_branch, char *line);
void get_num_instructions(int *transform_count, int *graphic_count, int *fractal_count);
void get_branch_count(int *graphics, int *fractals);
void read_file(Transform *transforms, Graphic *graphics, Fractal *fractals);

#endif //FRACTAL_CREATOR_FILE_READER_H