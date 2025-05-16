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

    while (fgets(fractal_information, 256, fptr)) {
        char *rest = fractal_information;
        token = strtok_r(fractal_information, " ", &rest);
        while (token != NULL) {
            if(strcmp(token,"TRANSFORM") == 0) {
                store_transform_information(rest);
            }
            else if(strcmp(token,"GRAPHIC") == 0) {
                store_transform_information(rest);
            }
            token = strtok_r(NULL, " ", &rest);
        }
    }

    fclose(fptr);
}

void store_transform_information(char *line) {
    struct Transform current_transform;
    char name[50];
    float rotation, scale;
    struct Coordinates translation;

    sscanf(line, "%s ROTATION %f TRANSLATION (%f,%f) SCALE %f", name, &rotation, &translation.x, &translation.y, &scale);

    current_transform.name = name;
    current_transform.rotation = rotation;
    current_transform.translation = translation;
    current_transform.scale = scale;

//    printf("Current TRANSFORM:\n"
//           "Name: %s\n"
//           "Rotation: %.2f\n"
//           "Translation: %.2f, %.2f\n"
//           "Scale: %.2f\n"
//           ,current_transform.name, current_transform.rotation, current_transform.translation.x,
//           current_transform.translation.y, current_transform.scale);
}



