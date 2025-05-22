//
// Created by Lukas Jonkus on 14/05/2025.
//

#include "shapes.h"
#include "svg_handler.h"
#include "main.h"


void draw_graphic(struct Graphic graphic) {
    struct Coordinates *coordinate;
    for (int i = 0; i < graphic.num_coordinates; i++) {
        coordinate = graphic.coordinates;
        create_points_to_draw(&graphic.coordinates[i]);
    }

    add_coordinates(&coordinate, graphic.num_coordinates);
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