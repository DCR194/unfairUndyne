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
void updatePosition(struct Box* box, int boxId);
void updateAllBoxes(struct Box** box);
void addBox(struct Box** boxPtr, int direction);
int checkHitbox(struct Box* boxPtr, int directionFacing);
void swap(int* a, int* b);


// HEX FUNCTIONS
int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);

// DRAWING FUNCTIONS
void initializeScreen();
//void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void plot_pixel(int x, int y, short int line_color);
void drawAllCubes(struct Box** boxes);
void drawCube(struct Box a);
void wait_for_vsync();
void clear_screen();
// void draw_line(int x0, int y0, int x1, int y1, short int line_color);


int numBoxes = 0;
int globalTime = 0;

short int Buffer1[YHEIGHT][XWIDTH + 200]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[YHEIGHT][XWIDTH + 200];

volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
volatile int pixel_buffer_start;

int main() {
    *(pixel_ctrl_ptr + 1) = (int)&Buffer1;
    wait_for_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    wait_for_vsync();

    clear_screen();


    struct Box* boxPtr = NULL;
    addBox(&boxPtr, 0); //add a left arrow;
    //addBox(&boxPtr, 1); // add a right arrow
    //addBox(&boxPtr, 0);

    //struct Box* boxPtr = NULL;
    //addBox(&boxPtr, 0);

    while (1) {
        drawCube(*boxPtr);
        //updatePosition(boxPtr);
        //updatePosition(boxPtr);
        updateAllBoxes(&boxPtr);
        wait_for_vsync();
        //clear_screen();
    }

}

void initializeScreen() {
    *(pixel_ctrl_ptr + 1) = (int)&Buffer1;
    wait_for_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    wait_for_vsync();



    clear_screen();

}

void drawAllCubes(struct Box** boxes) {
    if (numBoxes <= 0) return;
    for (int i = 0; i < numBoxes; i++) {
        drawCube(*boxes[i]);
    }
}

void drawCube(struct Box a) {
    for (int i = a.xPos - SIZECUBES / 2; i < a.xPos + SIZECUBES / 2; i++) {
        for (int j = a.yPos - SIZECUBES / 2; j < a.yPos + SIZECUBES / 2; j++) {
            plot_pixel(i, j, 0xF00F);
        }
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

void printBox(struct Box* box) {
    printf("xPos: %d, yPos: %d, xDir: %d, yDir: %d \n",
        box->xPos, box->yPos, box->xDir, box->yDir);
}

// Function to remove the first box (FIFO)
void removeBox(struct Box** boxPtr, int index) {
    if (numBoxes <= 0) return;
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
    if (direction == 0) { //  --->
        box->xPos = 0;
        box->yPos = YHEIGHT / 2;
        box->xDir = 1;
        box->yDir = 0;
    }
    if (direction == 1) { //  <---
        box->xPos = XWIDTH;
        box->yPos = YHEIGHT / 2;
        box->xDir = -1;
        box->yDir = 0;
    }
    if (direction == 2) { //Up
        box->xPos = 159;
        box->yPos = 0;
        box->xDir = 0;
        box->yDir = 1;
    }
    if (direction == 3) { //Down
        box->xPos = 159;
        box->yPos = 239;
        box->xDir = 0;
        box->yDir = -1;
    }
    box->direction = direction;
    // Add other conditions as needed
}

void updateAllBoxes(struct Box** box) {
    for (int i = 0; i < numBoxes; i++) {
        updatePosition(box[i], i);
    }
}

void updatePosition(struct Box* box, int boxId) {
    box->xPos += box->xDir;
    box->yPos += box->yDir;
    if (checkHitbox(box, box->direction) != 0) {
        removeBox(&box, boxId);
    }
}

int checkHitbox(struct Box* boxPtr, int directionFacing) {
    if ((boxPtr->direction == 0) && (boxPtr->xPos > ((XWIDTH / 2) - 5))) { // checking for --->
        if (boxPtr->xPos > XWIDTH / 2) {
            return -2;
        }
        else if (boxPtr->direction == directionFacing) {
            return -1;
        }
        else {
            return 0;
        }
    }
    if ((boxPtr->direction == 1) && (boxPtr->xPos - 159 > 30)) { // checking for <---
        if (boxPtr->xPos < XWIDTH / 2) {
            return -2;
        }
        else if (boxPtr->direction == directionFacing) {
            return -1;
        }
        else {
            return 0;
        }
    }

    if ((boxPtr->direction == 2) && (119 - boxPtr->yPos < 30)) { // checking for up arrows
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
    if ((boxPtr->direction == 3) && (boxPtr->yPos - 119 < 30)) { // checking for down arrows
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