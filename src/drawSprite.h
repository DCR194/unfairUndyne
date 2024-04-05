#ifndef DRAW_SPRITE_H
#define DRAW_SPRITE_H

#include <stdio.h>
#include <stdlib.h> 


volatile int pixel_buffer_start; // global variable

void plot_pixel(int x, int y, short int line_color); // plots one pixel
void draw_sprite(int x, int y, int spriteLength, int spriteWidth, short int pixel_color);


void draw_sprite(int x, int y, int spriteLength, int spriteWidth, short int pixel_color) {
    for (int i = 0; i < spriteLength; i++) {
        for (int j = 0; j < spriteWidth; j++) {
            plot_pixel(x + i, y + j, pixel_color);
        }
    }
}




void plot_pixel(int x, int y, short int pixel_color) {
    volatile short int* one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = pixel_color;
}

#endif