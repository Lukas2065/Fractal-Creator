//
// Created by Lukas Jonkus on 22/05/2025.
//

#include "svg_handler.h"

void initialize_svg_file() {
    FILE *file = fopen("../Fractal-UI/fractal.svg", "w");

    if (file == NULL) {
        perror("Error opening file");
    }

    fprintf(file, "<svg width=\"700\" height=\"700\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(file, "<rect x=\"0\" y=\"0\" width=\"700\" height=\"700\"\n"
                  "style=\"fill:white;stroke-width:3;stroke:black\" />\n");

    fclose(file);
}

void add_coordinates(Coordinates *coordinates, int num_coordinates) {
    FILE *file = fopen("../Fractal-UI/fractal.svg", "a");

    if (file == NULL) {
        perror("Error opening file");
    }

    fprintf(file, "<polyline points=\"");

    for (int i = 0; i < num_coordinates; ++i) {
        fprintf(file, "%.2f, %.2f ", coordinates[i].x, coordinates[i].y);
    }

    fprintf(file, "\" style=\"fill:none;stroke:black;stroke-width:1.0\"/>\n");
}

void close_svg_file() {
    FILE *file = fopen("../Fractal-UI/fractal.svg", "a");

    if (file == NULL) {
        perror("Error opening file");
    }

    fprintf(file, "</svg>\n");


    fclose(file);
}