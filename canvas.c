//
//  canvas.c
//  life
//
//  Created by Ксения Афанасьева on 26.11.17.
//  Copyright © 2017 Ксения Афанасьева. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "canvas.h"

#define true 1
typedef void (*neighbours_setter)(canvas *, cell *);
static int directions[][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

#pragma mark Prototypes
void set_cells_neighbours(canvas * canvas);
neighbours_setter get_neighbours_setter_func(canvas_type type);
void plain_type_neighbours(canvas * canvas, cell * cell);
void inf_type_neighbours(canvas * canvas, cell * cell);
void bottle_type_neighbours(canvas * canvas, cell * cell);

#pragma mark -
canvas * canvas_init(canvas_type type, unsigned int height, unsigned int width) {
    canvas * _canvas = (canvas *)malloc(sizeof(canvas));
    if(!_canvas) {
        return NULL;
    }
    
    _canvas->type = type;
    _canvas->height = height;
    _canvas->width = width;
    _canvas->cells = (cell ***)calloc(height, sizeof(cell **));
    if(!_canvas->cells) {
        free(_canvas);
        return NULL;
    }
    
    for(int y = 0; y < height; y++) {
        _canvas->cells[y] = (cell **)calloc(width, sizeof(cell *));
        if(!_canvas->cells[y]) {
            canvas_deinit(_canvas);
            return NULL;
        }
        for(int x = 0; x < width; x++) {
            _canvas->cells[y][x] = cell_init(x, y);
            if(!_canvas->cells[y][x]) {
                canvas_deinit(_canvas);
                return NULL;
            }
        }
    }
    
    set_cells_neighbours(_canvas);
    
    return _canvas;
}

void canvas_deinit(canvas * _canvas) {
    if(!_canvas) {
        return;
    }
    if(!_canvas->cells) {
        free(_canvas);
        return;
    }
    for(int i = 0; i < _canvas->height; i++) {
        if(!_canvas->cells[i]) {
            break;
        }
        for(int j = 0; j < _canvas->width; j++) {
            free(_canvas->cells[i][j]);
        }
        free(_canvas->cells[i]);
    }
    free(_canvas->cells);
    free(_canvas);
}

void set_cells_neighbours(canvas * _canvas) {
    neighbours_setter setter = get_neighbours_setter_func(_canvas->type);
    for(int y = 0; y < _canvas->height; y++) {
        for(int x = 0; x < _canvas->width; x++) {
            setter(_canvas, _canvas->cells[y][x]);
        }
    }
}

neighbours_setter get_neighbours_setter_func(canvas_type type) {
    switch (type) {
        case plain:
            return &plain_type_neighbours;
        case inf:
            return &inf_type_neighbours;
        case bottle:
            return &bottle_type_neighbours;
    }
}

void place_random_alive_cells(canvas * _canvas) {
    srand((unsigned int)time(NULL));
    int height = _canvas->height;
    int width = _canvas->width;
    int seed = width > height ? width : height;
    int num = seed + rand()%seed;
    for(int i = 0; i < num; i++) {
        _canvas->cells[rand()%height][rand()%width]->is_alive = true;
    }
}

void set_alive_cells(canvas * _canvas) {
    for(int y = 0; y < _canvas->height; y++) {
        for(int x = 0; x < _canvas->width; x++) {
            set_state(_canvas->cells[y][x]);
        }
    }
}

void print_canvas(canvas * _canvas) {
    for(int y = 0; y < _canvas->height; y++) {
        for(int x = 0; x < _canvas->width; x++) {
            char *s = _canvas->cells[y][x]->is_alive ? "ø" : " ";
            printf("%s", s);
        }
        printf("\n");
    }
}

#pragma mark Neighbours types functions
void plain_type_neighbours(canvas * _canvas, cell * _cell) {
    int x = _cell->coordinates.x;
    int y = _cell->coordinates.y;
    for(int i = 0; i < 8; i++) {
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];
        if(ny >= _canvas->height || ny < 0 ||
            nx >= _canvas->width || nx < 0) {
            _cell->neighbours[i] = NULL;
            continue;
        }
        _cell->neighbours[i] = _canvas->cells[ny][nx];
    }
}

void inf_type_neighbours(canvas * _canvas, cell * _cell) {
    int x = _cell->coordinates.x;
    int y = _cell->coordinates.y;
    for(int i = 0; i < 8; i++) {
        int ny = y + directions[i][0];
        ny = ny >= _canvas->height ? 0 : ny;
        ny = ny < 0 ? _canvas->height-1 : ny;
        int nx = x + directions[i][1];
        nx = nx >= _canvas->width ? 0 : nx;
        nx = nx < 0 ? _canvas->width-1 : nx;
        _cell->neighbours[i] = _canvas->cells[ny][nx];
    }
}

void bottle_type_neighbours(canvas * _canvas, cell * _cell) {
    int x = _cell->coordinates.x;
    int y = _cell->coordinates.y;
    for(int i = 0; i < 8; i++) {
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];
        if(ny < 0) {
            ny = _canvas->height-1;
            nx = (_canvas->width-1) - nx;
        }
        if(ny >= _canvas->height) {
            ny = 0;
            nx = (_canvas->width-1) - nx;
        }
        if(nx < 0) {
            nx = _canvas->width-1;
            ny = (_canvas->height-1) - ny;
        }
        if(nx >= _canvas->width) {
            nx = 0;
            ny = (_canvas->height-1) - ny;
        }
        if(nx == x && ny == y) {
            _cell->neighbours[i] = NULL;
            continue;
        }
        
        cell * neighbour = _canvas->cells[ny][nx];
        for(int j = 0; j < i; j++) {
            if(_cell->neighbours[j] == neighbour) {
                neighbour = NULL;
                break;
            }
        }
        
        _cell->neighbours[i] = neighbour;
    }
}
