//
//  cell.c
//  life
//
//  Created by Ксения Афанасьева on 13.11.17.
//  Copyright © 2017 Ксения Афанасьева. All rights reserved.
//

#include <stdlib.h>
#include "cell.h"

#define true 1
#define false 0

cell * cell_init(int x, int y) {
    cell * _cell = (cell *)malloc(sizeof(cell));
    if (!_cell) {
        return NULL;
    }
    
    _cell->coordinates.x = x;
    _cell->coordinates.y = y;
    
    return _cell;
}

void cell_deinit(cell * _cell) {
    free(_cell);
}

int alive_neighbours(cell * _cell) {
    int alive = 0;
    for(int i = 0; i < 8; i++) {
        cell * neighbour = _cell->neighbours[i];
        if(!neighbour) {
            continue;
        }
        alive += neighbour->is_alive;
    }
    
    return alive;
}

void set_state(cell * _cell) {
    int alive_n = alive_neighbours(_cell);
    if(_cell->is_alive) {
        if(alive_n < 2 || alive_n > 3) {
            _cell->is_alive = false;
        }
    } else {
        if (alive_n == 3) {
            _cell->is_alive = true;
        }
    }
}
