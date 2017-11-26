//
//  main.c
//  life
//
//  Created by Ксения Афанасьева on 13.11.17.
//  Copyright © 2017 Ксения Афанасьева. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
#define true 1
#define false 0
#define type bottle
#define h 15
#define w 20

int main() {
    
    canvas * _canvas = canvas_init(type, h, w);
    if(!_canvas) {
        return EXIT_FAILURE;
    }
    
    place_random_alive_cells(_canvas);
    
    while(true) {
        print_canvas(_canvas);
        set_alive_cells(_canvas);
        for(int i = 0; i < w; i++) {
            printf("_");
        }
        printf("\n");
        if(getchar()== 's') {
            break;
        }
    }
    
    canvas_deinit(_canvas);
    
    return 0;
}
