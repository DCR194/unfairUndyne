#ifndef DRAW_SPRITE_H
#define DRAW_SPRITE_H

#include <stdio.h>
#include <stdlib.h> 


// NEEDS SOME KIND OF INCLUDE FOR THE PLOT PIXEL TO WORK





volatile int pixel_buffer_start; // global variable

void plot_pixel(int x, int y, short int line_color); // plots one pixel
void draw_sprite(int x, int y, int spriteLength, int spriteWidth, short int pixel_color);


void draw_sprite(int x, int y, int spriteLength, int spriteWidth, short int pixel_color) {
    for (int i = 0; i < spriteLength; i++) {
        for (int j = 0; j < spriteWidth; j++) {
            // IF WE DO A HEADER FILE FOR DRAWING STUFF INCLUDE IT HERE

            //plot_pixel(x + i, y + j, pixel_color);
        }
    }
}

#endif