#define XWIDTH 320
#define YHEIGHT 240
#define SIZECUBES 10
#define NUMCUBES  7
#define ADDR_7SEG1 ((volatile long *) 0xFF200020)
#define ADDR_7SEG2 ((volatile long *) 0xFF200026)

#include <stdlib.h>
#include <stdbool.h>

volatile int* LEDaddress = 0xFF200040;

struct cube {
    int x;
    int y;
    int speed_x;
    int speed_y;
    short int color;
};

void plot_pixel(int x, int y, short int line_color); // plots one pixel
void clear_screen();
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void swap(int* a, int* b);
void drawCube(struct cube a, struct cube b);
int abs(int a);
void wait_for_vsync();
void initializeCube(struct cube* a);
void drawAllCubes(struct cube array[NUMCUBES]);
void initializeAllCubes(struct cube array[NUMCUBES]);
void updateAllCubes(struct cube array[NUMCUBES]);
void updateCube(struct cube* myCube);
void setupDarkCopies(struct cube source[NUMCUBES], struct cube dest[NUMCUBES]);
int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);


volatile int pixel_buffer_start; // global variable
short int Buffer1[YHEIGHT][XWIDTH + 200]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[YHEIGHT][XWIDTH + 200];



int main(void) {
    double globalTime = 0;
    struct cube pastCubes[NUMCUBES];
    struct cube myCubes[NUMCUBES];
    volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)

    initializeAllCubes(myCubes);
    setupDarkCopies(myCubes, pastCubes);

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
    updateAllCubes(myCubes);
    wait_for_vsync();


    while (1) {
        /* Erase any boxes and lines that were drawn in the last iteration */
        //...
        // code for drawing the boxes and lines (not shown)

        pixel_buffer_start = *(pixel_ctrl_ptr + 1);

        drawAllCubes(pastCubes);
        updateAllCubes(pastCubes);

        updateAllCubes(myCubes);
        drawAllCubes(myCubes);
        // code for updating the locations of boxes (not shown)

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync

        globalTime += (1.0 / 60.0);
        setSevenSegment(ADDR_7SEG1, (int)(globalTime));

        //pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}

// code for subroutines (not shown)

int getSWValue() {
    return *LEDaddress;
}

int decodeHex(int value) {
    int result;
    if (value == 0) {
        result = 0b0111111;
    }
    else if (value == 1) {
        result = 0b0000110;
    }
    else if (value == 2) {
        result = 0b1011011;
    }
    else if (value == 3) {
        result = 0b1001111;
    }
    else if (value == 4) {
        result = 0b1100110;

    }
    else if (value == 5) {
        result = 0b1101101;
    }
    else if (value == 6) {
        result = 0b1111101;
    }
    else if (value == 7) {
        result = 0b0000111;
    }
    else if (value == 8) {
        result = 0b1111111;
    }
    else if (value == 9) {
        result = 0b1100111;
    }
    else { return 0; }

    return result;

}

void setSevenSegment(volatile long* segAddress, int value) {

    int seg7;

    seg7 = decodeHex(value % 10);

    value /= 10;
    seg7 += decodeHex(value % 10) << 8;

    value /= 10;
    seg7 += decodeHex(value % 10) << 16;

    value /= 10;
    seg7 += decodeHex(value % 10) << 24;

    *segAddress = seg7;
}

void initializeCube(struct cube* a) {
    (*a).x = (rand() % (XWIDTH - SIZECUBES)) + SIZECUBES / 2;
    (*a).y = (rand() % (YHEIGHT - SIZECUBES)) + SIZECUBES / 2;
    (*a).speed_x = (((rand() % 2) * 2) - 1);
    (*a).speed_y = (((rand() % 2) * 2) - 1);
    (*a).color = rand();

}

void initializeAllCubes(struct cube array[NUMCUBES]) {
    for (int i = 0; i < NUMCUBES; i++) {
        initializeCube(&array[i]);
    }
}

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
        }
        error = error + deltay;
        if (error > 0) {
            y = y + y_step;
            error = error - deltax;
        }
    }
}

void drawCube(struct cube a, struct cube b) {
    for (int i = a.x - SIZECUBES / 2; i < a.x + SIZECUBES / 2; i++) {
        for (int j = a.y - SIZECUBES / 2; j < a.y + SIZECUBES / 2; j++) {
            plot_pixel(i, j, a.color);
        }
    }
    draw_line(b.x, b.y, a.x, a.y, a.color);
}

void drawAllCubes(struct cube array[NUMCUBES]) {
    for (int i = 0; i < NUMCUBES - 1; i++) {
        drawCube(array[i], array[i + 1]);
    }
    drawCube(array[NUMCUBES - 1], array[0]);
}

void setupDarkCopies(struct cube source[NUMCUBES], struct cube dest[NUMCUBES]) {
    for (int i = 0; i < NUMCUBES; i++) {
        dest[i] = source[i];
        dest[i].color = 0x00;
    }
}

bool outOfBoundsX(struct cube myCube) {
    return ((myCube.x >= XWIDTH - SIZECUBES / 2) || (myCube.x <= SIZECUBES / 2));
}

bool outOfBoundsY(struct cube myCube) {
    return ((myCube.y >= YHEIGHT - SIZECUBES / 2) || (myCube.y <= SIZECUBES / 2));
}

void updateCube(struct cube* myCube) {
    (*myCube).x += (*myCube).speed_x;
    (*myCube).y += (*myCube).speed_y;

    if (outOfBoundsX(*myCube)) {
        (*myCube).speed_x = -1 * (*myCube).speed_x;
        //updateCube(myCube);
        //(*myCube).x += (*myCube).speed_x;
    }
    if (outOfBoundsY(*myCube)) {
        (*myCube).speed_y = -1 * (*myCube).speed_y;
        //updateCube(myCube);
        //(*myCube).y += (*myCube).speed_y;
    }
}

void updateAllCubes(struct cube array[NUMCUBES]) {
    for (int i = 0; i < NUMCUBES; i++) {
        updateCube(&array[i]);
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
