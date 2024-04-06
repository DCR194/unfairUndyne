// 'pixil-frame-0 (2)', 320x240px
#define XWIDTH 320
#define YHEIGHT 240
#define SIZECUBES 10
#define NUMCUBES  7

#include <stdlib.h>
#include <stdbool.h>
#include "backgrounds.h"

volatile int* SWaddress = 0xFF200040;


void plot_pixel(int x, int y, short int line_color); // plots one pixel
void clear_screen();
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void swap(int* a, int* b);
//void drawCube(struct cube a, struct cube b);
int abs(int a);
void wait_for_vsync();

int getSWValue() {
    return *SWaddress;
}

volatile int pixel_buffer_start; // global variable
short int Buffer1[YHEIGHT][XWIDTH + 200]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[YHEIGHT][XWIDTH + 200];
short int *backGround;


int main(void) {
    volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)

    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int)&Buffer1; // first store the address in the  back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer
    wait_for_vsync();

    /*
    while (1) {
        / Erase any boxes and lines that were drawn in the last iteration /
        //...
        // code for drawing the boxes and lines (not shown)

        pixel_buffer_start = *(pixel_ctrl_ptr + 1);

        // code for updating the locations of boxes (not shown)

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync

        //pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
    */

    while (1) {
        if (getSWValue() == 1){
            backGround = easyBG;
        }else{
            backGround = hardBG;
        }
        clear_screen();
        wait_for_vsync();
    }
}

// code for subroutines (not shown)


void plot_pixel(int x, int y, short int line_color) {
    volatile short int* one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = line_color;
}

void clear_screen() {
    int y, x;
    /*for (x = 0; x < 320; x++)
        for (y = 0; y < 240; y++)
            plot_pixel(x, y, 0);*/
    short int color;
    for (x = 0; x < XWIDTH; x++) {
        for (y = 0; y < YHEIGHT; y++) {
            color = backGround[x + (y * XWIDTH)];
            plot_pixel(x, y, color);
        }
    }
}

void draw_line(int x0, int y0, int x1, int y1, short int line_color) {
    bool is_steep = abs(y1 - y0) > abs(x1 - x0);
    if (is_steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax / 2);
    int y = y0;
    int y_step;
    if (y0 < y1) {
        y_step = 1;
    }
    else {
        y_step = -1;
    }

    for (int x = x0; x < x1; x++) {
        if (is_steep) {
            plot_pixel(y, x, line_color);
        }
        else {
            plot_pixel(x, y, line_color);
        }
        error = error + deltay;
        if (error > 0) {
            y = y + y_step;
            error = error - deltax;
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    (*a) = (*b);
    (*b) = temp;
}

int abs(int a) {
    if (a > 0) {
        return a;
    }
    else {
        return -1 * a;
    }
}

void wait_for_vsync() {
    volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
    *pixel_ctrl_ptr = 1;
    int status;
    while (1) {
        status = *(pixel_ctrl_ptr + 3);
        if ((status & 1) == 0) {
            return;
        }
    }
}

