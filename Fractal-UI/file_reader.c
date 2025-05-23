//
// Created by Lukas Jonkus on 16/05/2025.
//

#include "file_reader.h"


void read_file(Transform *transforms, Graphic *graphics, Fractal *fractals) {
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("../Fractal-UI/NSFS1.txt", "r");
    if(fptr == NULL) {
        printf("Not able to open the file.");
    }

    char fractal_information[256];
    char *token;
    int count;
    int transform_count = 0;
    int graphic_count = 0;
    int fractal_count = 0;
    int graphic_branch_count = 0;
    int fractal_branch_count = 0;


    while (fgets(fractal_information, 256, fptr)) {
        char *rest = fractal_information;
        token = strtok_r(fractal_information, " ", &rest);
        count = 0;
        while (token != NULL) {
            if(strcmp(token,"TRANSFORM") == 0 && count == 0) {
                Transform current_transform = store_transform_information(rest);
                transforms[transform_count] = current_transform;
                transform_count++;
            }
            else if(strcmp(token,"GRAPHIC") == 0 && count == 0) {
                Graphic current_graphic = store_graphic_information(rest);
                graphics[graphic_count] = current_graphic;
                graphic_count++;
            }
            else if(strcmp(token,"FRACTAL") == 0 && count == 0) {
                fractals[fractal_count] = store_fractal_information(rest);
                graphic_branch_count = 0;
                fractal_branch_count = 0;
                fractal_count++;
            }
            else if(strcmp(token,"BRANCH") == 0 && count == 0) {
                store_branch_information(&fractals[fractal_count-1], transforms, graphics, fractals, transform_count ,graphic_count, fractal_count, &graphic_branch_count, &fractal_branch_count ,rest);
            }
            count++;
            token = strtok_r(NULL, " ", &rest);
        }
    }

    fclose(fptr);
}

void get_num_instructions(int *transform_count, int *graphic_count, int *fractal_count) {
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
                (*transform_count)++;
            }
            else if(strcmp(token,"GRAPHIC") == 0 && count == 0) {
                (*graphic_count)++;
            }
            else if(strcmp(token,"FRACTAL") == 0 && count == 0) {
                (*fractal_count)++;
            }
            count++;
            token = strtok_r(NULL, " ", &rest);
        }
    }

    fclose(fptr);
}

void get_branch_count(int *graphics, int *fractals) {
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("../Fractal-UI/NSFS1.txt", "r");
    if(fptr == NULL) {
        printf("Not able to open the file.");
    }

    char fractal_information[256];
    char *token;
    int count;
    int fractal_count = 0;

    while (fgets(fractal_information, 256, fptr)) {
        char *rest = fractal_information;
        token = strtok_r(fractal_information, " ", &rest);
        count = 0;
        while (token != NULL) {
            if(strcmp(token,"FRACTAL") == 0 && count == 0) {
                fractal_count++;
            }
            else if (strcmp(token, "GRAPHIC") == 0 && count != 0) {
                graphics[fractal_count - 1]++;
            } else if (strcmp(token, "FRACTAL") == 0 && count != 0) {
                fractals[fractal_count - 1]++;
            }
            count++;
            token = strtok_r(NULL, " ", &rest);
        }
    }

    fclose(fptr);
}

Fractal store_fractal_information(char *line) {
    Fractal current_fractal;
    char name[50];
    sscanf(line, "%s", name);
    current_fractal.name = strdup(name);
    return current_fractal;
}

void store_branch_information(Fractal *current_fractal, Transform *transforms, Graphic *graphics, Fractal *fractals, int transform_count, int graphic_count, int fractal_count, int *current_graphic_branch, int *current_fractal_branch, char *line) {
    char transform_name[50];
    int start_iteration, end_iteration;
    char type[50];
    char type_name[50];

    sscanf(line, "%s [%i:%i] %s %s", transform_name, &start_iteration, &end_iteration, type, type_name);
    printf("Current Fractal: %s\n", current_fractal->name);

    if(strcmp(type, "GRAPHIC") == 0) {
        Graphic_branch current_branch;
        current_branch.start_iteration = start_iteration;
        current_branch.end_iteration = end_iteration;
        for (int i = 0; i < transform_count; ++i) {
            if(strcmp(transform_name, transforms[i].name) == 0) {
                current_branch.transform = &transforms[*current_graphic_branch];
                //printf("TRANSFORM: %s, is in FRACTAL: %s\n", transforms[i].name, current_fractal->name);
            }
        }
        for (int i = 0; i < graphic_count; ++i) {
            if(strcmp(type_name, graphics[i].name) == 0) {
                current_branch.graphic = &graphics[*current_graphic_branch];
                //printf("GRAPHIC: %s, is in FRACTAL: %s\n", graphics[i].name, current_fractal->name);
            }
        }
        printf("fractal_count: %i, current_graphic_branch: %i\n", fractal_count-1, *current_graphic_branch);
        current_fractal->graphic_branches[*current_graphic_branch] = current_branch;
        (*current_graphic_branch)++;
    }
    else if(strcmp(type, "FRACTAL") == 0) {
        Fractal_branch current_branch;
        current_branch.start_iteration = start_iteration;
        current_branch.end_iteration = end_iteration;
        for (int i = 0; i < transform_count; ++i) {
            if (strcmp(transform_name, transforms[i].name) == 0) {
                current_branch.transform = &transforms[*current_fractal_branch];
                //printf("TRANSFORM: %s, is in FRACTAL: %s\n", transforms[i].name, current_fractal->name);
            }
        }
        for (int i = 0; i < fractal_count; ++i) {
            if (strcmp(type_name, fractals[i].name) == 0) {
                current_branch.fractal = &fractals[*current_fractal_branch];
                //printf("FRACTAL: %s, is in FRACTAL: %s\n", fractals[i].name, current_fractal->name);
            }
        }
        printf("fractal_count: %i, current_fractal_branch: %i\n", fractal_count-1, *current_fractal_branch);
        current_fractal->fractal_branches[*current_fractal_branch] = current_branch;
        (*current_fractal_branch)++;
    }

}

Transform store_transform_information(char *line) {
    struct Transform current_transform;
    char name[50];
    float rotation, scale;
    struct Coordinates translation;

    sscanf(line, "%s ROTATION %f TRANSLATION (%f,%f) SCALE %f", name, &rotation, &translation.x, &translation.y, &scale);

    current_transform.name = strdup(name);
    current_transform.rotation = rotation;
    current_transform.translation = translation;
    current_transform.scale = scale;

    return current_transform;
}

Graphic store_graphic_information(char *line) {
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

    current_graphic.name = strdup(name);

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



