//
// Created by Lukas Jonkus on 16/05/2025.
//

#include "main.h"
#include "shapes.h"

#ifndef FRACTAL_CREATOR_FILE_READER_H
#define FRACTAL_CREATOR_FILE_READER_H

int get_num_coordinates(char *line);
void get_coordinates(char *string_coordinates, struct Coordinates *coordinates);
struct Graphic store_graphic_information(char *line);
void store_transform_information(char *line);
void read_file(struct SDL_Components* sdl_components);

#endif //FRACTAL_CREATOR_FILE_READER_H