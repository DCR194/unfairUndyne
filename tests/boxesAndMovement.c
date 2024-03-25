#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#define SIZECUBES 5
#define XWIDTH 320
#define YHEIGHT 240


struct Box {
    int xPos;
    int yPos;
    int xDir;
    int yDir;
    int direction;
};

// LOGIC FUNCTIONS
void printBox(struct Box* box);
void removeBox(struct Box** boxPtr, int index);
void setBoxValues(struct Box* box, int direction);
void updatePosition(struct Box* box);
void addBox(struct Box** boxPtr, int direction);
int checkHitbox(struct Box* boxPtr, int directionFacing);
void swap(int* a, int* b);


// HEX FUNCTIONS
int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);

// DRAWING FUNCTIONS
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void plot_pixel(int x, int y, short int line_color);
void drawCube(struct Box a, struct Box b);
void wait_for_vsync();
void clear_screen();
void draw_line(int x0, int y0, int x1, int y1, short int line_color);


int numBoxes = 0;
int globalTime = 0;

short int Buffer1[YHEIGHT][XWIDTH + 200]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[YHEIGHT][XWIDTH + 200];

volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
volatile int pixel_buffer_start;

int main() {
    struct Box* boxPtr = NULL;

    clear_screen();
    wait_for_vsync();

    while (1) {

    }

}



void drawCube(struct Box a, struct Box b) {
    for (int i = a.xPos - SIZECUBES / 2; i < a.xPos + SIZECUBES / 2; i++) {
        for (int j = a.yPos - SIZECUBES / 2; j < a.yPos + SIZECUBES / 2; j++) {
            plot_pixel(i, j, 0xFFFF);
        }
    }
    draw_line(b.xPos, b.yPos, a.xPos, a.yPos, 0xFFFF);
}

void plot_pixel(int x, int y, short int line_color) {
    volatile short int* one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = line_color;
}

// void drawBox(struct Box* myBox){

//}

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

void clear_screen() {
    int y, x;
    for (x = 0; x < 320; x++)
        for (y = 0; y < 240; y++)
            plot_pixel(x, y, 0);
}

void printBox(struct Box* box) {
    printf("xPos: %d, yPos: %d, xDir: %d, yDir: %d \n",
        box->xPos, box->yPos, box->xDir, box->yDir);
}

// Function to remove the first box (FIFO)
void removeBox(struct Box** boxPtr, int index) {
    // Check if the index is valid
    if (index < 0 || index >= numBoxes) {
        printf("Invalid index\n");
        return;
    }

    // Free the memory occupied by the box at the specified index
    // free(&(*boxPtr)[index]);

    // Shift the memory to the left to remove the box
    for (int i = index; i < numBoxes - 1; i++) {
        (*boxPtr)[i] = (*boxPtr)[i + 1];
    }

    // Reallocate memory to decrease the size of the box array
    *boxPtr = (struct Box*)realloc(*boxPtr, (numBoxes - 1) * sizeof(struct Box));

    // Decrement the number of boxes
    numBoxes--;
}

// Function to initialize the attributes of the newest box
void setBoxValues(struct Box* box, int direction) {
    // Set position and direction values based on the direction parameter
    if (direction == 0) { //Laft
        box->xPos = 0;
        box->yPos = 119;
        box->xDir = 1;
        box->yDir = 0;
    }
    if (direction == 0) { //Right
        box->xPos = 319;
        box->yPos = 119;
        box->xDir = -1;
        box->yDir = 0;
    }
    if (direction == 0) { //Up
        box->xPos = 159;
        box->yPos = 0;
        box->xDir = 0;
        box->yDir = 1;
    }
    if (direction == 0) { //Down
        box->xPos = 159;
        box->yPos = 239;
        box->xDir = 0;
        box->yDir = -1;
    }
    // Add other conditions as needed
}

void updatePosition(struct Box* box) {
    box->xPos += box->xDir;
    box->yPos += box->yDir;
}

int checkHitbox(struct Box* boxPtr, int directionFacing) {
    if (boxPtr->direction == 0 && (159 - boxPtr->xPos < 30)) { // checking for left arrows
        if (159 - boxPtr->xPos < 9) {
            return -2;
        }
        else if (boxPtr->direction == directionFacing) {
            return -1;
        }
        else {
            return 0;
        }
    }
    if (boxPtr->direction == 1 && (boxPtr->xPos - 159 < 30)) { // checking for right arrows
        if (boxPtr->xPos - 159 < 9) {
            return -2;
        }
        else if (boxPtr->direction == directionFacing) {
            return -1;
        }
        else {
            return 0;
        }
    }

    if (boxPtr->direction == 2 && (119 - boxPtr->yPos < 30)) { // checking for left arrows
        if (119 - boxPtr->yPos < 9) {
            return -2;
        }
        else if (boxPtr->direction == directionFacing) {
            return -1;
        }
        else {
            return 0;
        }
    }
    if (boxPtr->direction == 3 && (boxPtr->yPos - 119 < 30)) { // checking for left arrows
        if (boxPtr->yPos - 119 < 9) {
            return -2;
        }
        else if (boxPtr->direction == directionFacing) {
            return -1;
        }
        else {
            return 0;
        }
    }

    return 0;
}

// Function to add a box
void addBox(struct Box** boxPtr, int direction) {
    // Reallocate memory to increase the size of the box array
    *boxPtr = (struct Box*)realloc(*boxPtr, (numBoxes + 1) * sizeof(struct Box));

    // Check if memory reallocation was successful
    if (*boxPtr == NULL) {
        printf("Memory reallocation failed\n");
        return;
    }

    // Increment the number of boxes
    numBoxes++;

    // Call setBoxValues to initialize the attributes of the newest box
    setBoxValues(&(*boxPtr)[numBoxes - 1], direction);
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

void swap(int* a, int* b) {
    int temp = *a;
    (*a) = (*b);
    (*b) = temp;
}