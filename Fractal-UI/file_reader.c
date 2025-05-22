//
// Created by Lukas Jonkus on 16/05/2025.
//

#include "file_reader.h"

void read_file() {
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("../Fractal-UI/NSFS1.txt", "r");
    if(fptr == NULL) {
        printf("Not able to open the file.");
    }

    char fractal_information[256];
    char *token;
    int count;

    while (fgets(fractal_information, 256, fptr)) {
        char *rest = fractal_information;
        token = strtok_r(fractal_information, " ", &rest);
        count = 0;
        while (token != NULL) {
            if(strcmp(token,"TRANSFORM") == 0 && count == 0) {
                store_transform_information(rest);
            }
            else if(strcmp(token,"GRAPHIC") == 0 && count == 0) {
                struct Graphic current_graphic = store_graphic_information(rest);
                draw_graphic(current_graphic);
            } else if(strcmp(token,"FRACTAL") == 0 && count == 0) {

            }
            count++;
            token = strtok_r(NULL, " ", &rest);
        }
    }

    fclose(fptr);
}

void get_num_instructions() {

}

struct Transform store_transform_information(char *line) {
    struct Transform current_transform;
    char name[50];
    float rotation, scale;
    struct Coordinates translation;

    sscanf(line, "%s ROTATION %f TRANSLATION (%f,%f) SCALE %f", name, &rotation, &translation.x, &translation.y, &scale);

    current_transform.name = name;
    current_transform.rotation = rotation;
    current_transform.translation = translation;
    current_transform.scale = scale;

    return current_transform;
}

struct Graphic store_graphic_information(char *line) {
    struct Graphic current_graphic;
    char name[50];

    int vertex_count;
    vertex_count = get_num_coordinates(line);

    current_graphic.num_coordinates = vertex_count;
    current_graphic.coordinates = calloc(current_graphic.num_coordinates, sizeof(struct Coordinates));


    struct Coordinates current_vertex;

    char *token;
    char *rest = line;
    token = strtok_r(line, " ", &rest);
    bool isName = true;
    int count = 0;
    while (token != NULL) {
        if (isName) {
            strcpy(name, token);
            isName = false;
        } else {
            get_coordinates(token, &current_vertex);
            current_graphic.coordinates[count].x = current_vertex.x;
            current_graphic.coordinates[count].y = current_vertex.y;
            count++;
        }
        token = strtok_r(NULL, " ", &rest);
    }

    return current_graphic;

}

int get_num_coordinates(char *line) {
    char *token;
    char line_copy[100];
    strcpy(line_copy, line);
    char *rest = line_copy;

    token = strtok_r(line_copy, " ", &rest);
    int vertex_count = 0;
    bool isName = true;
    while (token != NULL) {
        if(isName) {
            isName = false;
        } else {
            vertex_count++;
        }
        token = strtok_r(NULL, " ", &rest);
    }

    return vertex_count;
}

void get_coordinates(char *string_coordinates, Coordinates *coordinates) {
    sscanf(string_coordinates, "(%f,%f)",&coordinates->x, &coordinates->y);
}



