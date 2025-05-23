//
// Created by Lukas Jonkus on 14/05/2025.
//

#include "shapes.h"
#include "file_reader.h"
#include "svg_handler.h"
#include "main.h"


void get_instructions() {
    int transform_count = 0;
    int graphic_count = 0;
    int fractal_count = 0;

    get_num_instructions(&transform_count, &graphic_count, &fractal_count);

    int *graphic_branch_count = calloc(fractal_count, sizeof(int));
    int *fractal_branch_count = calloc(fractal_count, sizeof(int));

    get_branch_count(graphic_branch_count, fractal_branch_count);

//    printf("TRANSFORMS: %i\n"
//           "GRAPHICS: %i\n"
//           "FRACTALS: %i\n"
//            , transform_count, graphic_count, fractal_count);
//
//    for (int i = 0; i < fractal_count; ++i) {
//        printf("FRACTAL NO: %i\n"
//               "GRAPHIC BRANCH: %i\n"
//               "FRACTAL BRANCH: %i\n",
//               i, graphic_branch_count[i], fractal_branch_count[i]);
//    }

    store_instructions(transform_count,graphic_count,fractal_count,graphic_branch_count,fractal_branch_count);
}

void store_instructions(int transform_count, int graphic_count, int fractal_count, int *graphic_branch_count, int *fractal_branch_count) {
    Transform *transforms = calloc(transform_count, sizeof (Transform));
    Graphic *graphics = calloc(graphic_count, sizeof (Graphic));
    Fractal *fractals = calloc(fractal_count, sizeof (Fractal));

    for (int i = 0; i < fractal_count; ++i) {
        fractals[i].num_graphic_branches = graphic_branch_count[i];
        fractals[i].num_fractal_branches = fractal_branch_count[i];

        fractals[i].graphic_branches = calloc(fractals[i].num_graphic_branches, sizeof(Graphic_branch));
        fractals[i].fractal_branches = calloc(fractals[i].num_fractal_branches, sizeof(Fractal_branch));

        printf("%i, %i\n", fractals[i].num_graphic_branches, fractals[i].num_fractal_branches);
    }


    read_file(transforms, graphics, fractals);

//    for (int i = 0; i < fractal_count; ++i) {
//        printf("FRACTAL: %s\n", fractals[i].name);
//        printf("%i\n", fractals[i].num_graphic_branches);
//        for (int j = 0; j < fractals[i].num_graphic_branches; ++j) {
//            printf("TRANSFORM: %s\n", fractals[i].graphic_branches[j].transform->name);
//            printf("GRAPHIC: %s\n", fractals[i].graphic_branches[j].graphic->name);
//        }
//        for (int j = 0; j < fractals[i].num_fractal_branches; ++j) {
//            printf("TRANSFORM: %s\n", fractals[i].fractal_branches[j].transform->name);
//            printf("FRACTAL: %s\n", fractals[i].fractal_branches[j].fractal->name);
//        }
//    }
}

void draw_graphic(Graphic graphic) {
    Coordinates *coordinate;
    coordinate = graphic.coordinates;
    for (int i = 0; i < graphic.num_coordinates; i++) {
        create_points_to_draw(&graphic.coordinates[i]);
    }

    add_coordinates(coordinate, graphic.num_coordinates);
}

void create_points_to_draw(Coordinates *coordinates) {
    //flip_points(coordinates);
    centralise_points(coordinates);
}

void flip_points(Coordinates *coordinates) {
    coordinates->x = coordinates->x * -1;
    coordinates->y = coordinates->y * -1;
}

void centralise_points(Coordinates *coordinates) {
    coordinates->x = coordinates->x + SCREEN_WIDTH/2;
    coordinates->y = coordinates->y + SCREEN_HEIGHT/2;
}


/**
 * function to rotate a translation vector or a coordinate (rotated around the origin)
 * @param rotation - the rotation angle in degrees
 * @param tr - the translation or Coordinate to be rotated
 * @return - a new Translation is returned - caller must free the memory allocated.
 */
Translation* rotate(double rotation_angle, Translation* tr) {
    // create a new Translation to hold the transformed point
    Translation* result_tr = (Translation*)malloc(sizeof(Translation));
    // convert the rotation to radians
    double radians = rotation_angle * (M_PI / 180);
    // apply the rotation
    result_tr->x = tr->x * cos(radians) - tr->y * sin(radians);
    result_tr->y = tr->x * sin(radians) + tr->y * cos(radians);
    return result_tr;
}