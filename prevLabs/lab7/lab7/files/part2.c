#define XWIDTH 320
#define YHEIGHT 240

#include <stdbool.h>
void plot_pixel(int x, int y, short int line_color); // plots one pixel
void clear_screen();
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void swap(int* a, int* b);
int abs(int a);
void wait_for_vsync();


int pixel_buffer_start; // global variable

int main(void) {
    volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    int yPosition = 2;
    int speed = 1;
    int x_start = XWIDTH / 4;
    int x_end = x_start * 3;

    pixel_buffer_start = *pixel_ctrl_ptr;
    while (1) {

        draw_line(x_start, yPosition - speed, x_end, yPosition - speed, 0x000000);
        draw_line(x_start, yPosition, x_end, yPosition, 0xff0000);
        if (yPosition == 0) speed = 1;
        if (yPosition == YHEIGHT) speed = -1;
        yPosition += speed;
        wait_for_vsync();
    }


}

// code not shown for clear_screen() and draw_line() subroutines


void plot_pixel(int x, int y, short int line_color) {
    volatile short int* one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = line_color;
}
void clear_screen() {
    int y, x;
    for (x = 0; x < 320; x++)
        for (y = 0; y < 240; y++)
            plot_pixel(x, y, 0);
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
            error = error + deltay;
            if (error > 0) {
                y = y + y_step;
                error = error - deltax;
            }
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