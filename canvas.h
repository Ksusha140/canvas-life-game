//
//  canvas.h
//  life
//
//  Created by Ксения Афанасьева on 26.11.17.
//  Copyright © 2017 Ксения Афанасьева. All rights reserved.
//

#ifndef canvas_h
#define canvas_h

#include "cell.h"

typedef enum canvas_type {
    plain,
    inf,
    bottle
} canvas_type;

typedef struct canvas {
    unsigned int width;
    unsigned int height;
    canvas_type type;
    cell *** cells;
} canvas;

canvas * canvas_init(canvas_type type, unsigned int height, unsigned int width);
void canvas_deinit(canvas * canvas);
void place_random_alive_cells(canvas * canvas);
void set_alive_cells(canvas * canvas);
void print_canvas(canvas * canvas);

#endif /* canvas_h */
