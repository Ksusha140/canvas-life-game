//
//  cell.h
//  life
//
//  Created by Ксения Афанасьева on 13.11.17.
//  Copyright © 2017 Ксения Афанасьева. All rights reserved.
//

#ifndef cell_h
#define cell_h

typedef struct cell {
    struct {
        int x;
        int y;
    } coordinates;
    struct cell * neighbours[8];
    int is_alive;
} cell;

cell * cell_init(int x, int y);
void cell_deinit(cell * cell);
void set_state(cell * cell);

#endif /* cell_h */
