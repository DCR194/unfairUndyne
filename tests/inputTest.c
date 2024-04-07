#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "mediaobj.h"
#include "magicNumbers.h"

const short int arrowSprite[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0xffff, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000,
    0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};


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
void updateAllBoxes(struct Box* box);
void addBox(struct Box** boxPtr, int direction);
int checkHitbox(struct Box* boxPtr);
void checkAllBoxes(struct Box* boxPtr);
void swap(int* a, int* b);
int checkUserInput();


// HEX FUNCTIONS
int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);

// DRAWING FUNCTIONS
void initializeScreen();
//void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void plot_pixel(int x, int y, short int line_color);
void drawAllCubes(struct Box* boxes);
void drawCube(struct Box* a);
void wait_for_vsync();
void clear_screen();
void eraseAllArrows(struct Box* boxes);
void GameLogic(struct Box* boxPtr);
// void draw_line(int x0, int y0, int x1, int y1, short int line_color);


int numBoxes = 0;
int globalTime = 0;
int directionFacing = 0;
int coolDown = 15;
char key = 0;


short int Buffer1[YHEIGHT][XWIDTH + 200]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[YHEIGHT][XWIDTH + 200];

volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
volatile int pixel_buffer_start;

bool hit_flag = false;

//  volatile int* pixel_ctrl_ptr = (int*)0xFF203020;

int main() {
    struct Box* boxPtr = NULL;

    printf("\nnumboxes: %d\n", numBoxes);


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
    // updateAllCubes(myCubes);
    wait_for_vsync();
    addBox(&boxPtr, 0);
    addBox(&boxPtr, 1);
    while (1) {

        pixel_buffer_start = *(pixel_ctrl_ptr + 1);

        eraseAllArrows(boxPtr);
        // updateAllBoxes(boxPtr);
        // checkAllBoxes(boxPtr);
        GameLogic(boxPtr);
        printBox(&boxPtr[0]);


        drawAllCubes(boxPtr);

        wait_for_vsync();

    }

}

bool inBounds(int x, int y) {
    return (x < XWIDTH) && (x >= 0) && (y < YHEIGHT) && (y >= 0);
}

void drawRightArrow(struct Box* a) {
    for (int x = 0; x < ARROWBOXWIDTH; x++) {
        for (int y = 0; y < ARROWBOXWIDTH; y++) {
            if (inBounds(a->xPos + x, a->yPos + y)) {
                if (arrowSprite[x + (y * ARROWBOXWIDTH)] != 0x0000) {
                    plot_pixel(a->xPos + x - (ARROWBOXWIDTH / 2),
                        a->yPos + y - (ARROWBOXWIDTH / 2),
                        arrowSprite[x + (y * ARROWBOXWIDTH)]);
                }
            }
        }
    }
}

void eraseSmartArrow(struct Box* a) {
    for (int x = 0 - abs(a->xDir); x < ARROWBOXWIDTH - abs(a->xDir); x++) {
        for (int y = 0 /*- a->yDir*/; y < ARROWBOXWIDTH /*- a->yDir*/; y++) {
            if (inBounds(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)), a->yPos + y)) {
                //if (arrowSprite[x + (y * ARROWBOXWIDTH)] != 0x0000) {
                plot_pixel(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)),
                    a->yPos + y - (ARROWBOXWIDTH / 2),
                    0x0000);
                //}
            }
        }
    }
}

void eraseCollidedArrow(struct Box* a) {
    for (int x = 0 - abs(a->xDir); x < ARROWBOXWIDTH - abs(a->xDir); x++) {
        for (int y = 0 /*- a->yDir*/; y < ARROWBOXWIDTH /*- a->yDir*/; y++) {
            if (inBounds(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)), a->yPos + y)) {
                //if (arrowSprite[x + (y * ARROWBOXWIDTH)] != 0x0000) {
                plot_pixel(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)),
                    a->yPos + y - (ARROWBOXWIDTH / 2),
                    0x0000);
                //}
            }
        }
    }
}

void eraseAllArrows(struct Box* boxes) {
    if (numBoxes <= 0) return;
    for (int i = 0; i < numBoxes; i++) {
        if ((&boxes[i])->direction < 2) {
            eraseCollidedArrow(&boxes[i]);
        }

    }
}

void drawSmartArrow(struct Box* a) { // draw the arrows but put a little thought into it
    for (int x = 0; x < ARROWBOXWIDTH; x++) {
        for (int y = 0; y < ARROWBOXWIDTH; y++) {
            if (inBounds(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)), a->yPos + y)) {
                if (arrowSprite[x + (y * ARROWBOXWIDTH)] != 0x0000) {
                    plot_pixel(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)),
                        a->yPos + y - (ARROWBOXWIDTH / 2),
                        arrowSprite[x + (y * ARROWBOXWIDTH)]);
                }
            }
        }
    }
    //plot_pixel(a->xPos, a->yPos, 0xff00);
    //plot_pixel(a->xPos + 1, a->yPos, 0x0000);

}

void drawAllCubes(struct Box* boxes) {
    if (numBoxes <= 0) return;
    for (int i = 0; i < numBoxes; i++) {
        if ((&boxes[i])->direction < 2) {
            drawSmartArrow(&boxes[i]);
        }
        else {
            drawCube(&boxes[i]);
        }
    }
}

void drawCube(struct Box* a) {
    for (int i = a->xPos - SIZECUBES / 2; i < a->xPos + SIZECUBES / 2; i++) {
        for (int j = a->yPos - SIZECUBES / 2; j < a->yPos + SIZECUBES / 2; j++) {
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
    // Check if the index is valid
    if (index < 0 || index >= numBoxes) {
        printf("Invalid index\n");
        return;
    }

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
        box->xDir = 5;
        box->yDir = 0;
    }
    if (direction == 1) { //  <---
        box->xPos = XWIDTH;
        box->yPos = YHEIGHT / 2;
        box->xDir = -5;
        box->yDir = 0;
    }
    if (direction == 2) { //Up
        box->xPos = 159;
        box->yPos = 0;
        box->xDir = 0;
        box->yDir = 5;
    }
    if (direction == 3) { //Down
        box->xPos = 159;
        box->yPos = 239;
        box->xDir = 0;
        box->yDir = -5;
    }
    box->direction = direction;
    // Add other conditions as needed
}

void updateAllBoxes(struct Box* boxes) {
    for (int i = 0; i < numBoxes; i++) {
        updatePosition(&boxes[i]);
        /*
        if (checkHitbox(boxes[i], (boxes[i])->direction) != 0) {
            removeBox(boxes, i);
        }
        */
    }
}

void updatePosition(struct Box* box) {
    box->xPos += box->xDir;
    box->yPos += box->yDir;

}

int checkHitbox(struct Box* boxPtr) {
    if (boxPtr->direction == 0 && 159 - boxPtr->xPos < 30) { //Left arrow hitboxes
        if (159 - boxPtr->xPos < 9) {
            return -2;
        }
        else if (directionFacing == 0) {
            return -1;
        }
        else {
            return 0;
        }
    }

    if (boxPtr->direction == 1 && boxPtr->xPos - 159 < 30) { //Right arrow hitboxes
        if (boxPtr->xPos - 159 < 9) {
            return -2;
        }
        else if (directionFacing == 1) {
            return -1;
        }
        else {
            return 0;
        }
    }

    if (boxPtr->direction == 2 && 119 - boxPtr->yPos < 30) { //Up arrow hitboxes
        if (119 - boxPtr->yPos < 9) {
            return -2;
        }
        else if (directionFacing == 2) {
            return -1;
        }
        else {
            return 0;
        }
    }

    if (boxPtr->direction == 3 && boxPtr->yPos - 119 < 30) { //Down arrow hitboxes
        if (boxPtr->yPos - 119 < 9) {
            return -2;
        }
        else if (directionFacing == 3) {
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

void checkAllBoxes(struct Box* boxPtr) {
    for (int i = numBoxes - 1; i >= 0; i--) {
        int hit_type = checkHitbox(&boxPtr[i]);
        if (hit_type == -2) {
            pixel_buffer_start = *(pixel_ctrl_ptr);
            eraseCollidedArrow(&boxPtr[i]);
            pixel_buffer_start = *(pixel_ctrl_ptr + 1);
            removeBox(&boxPtr, i);
            hit_flag = true;
            hit_reset = true;
        }
        else if (hit_type == -1){
            pixel_buffer_start = *(pixel_ctrl_ptr);
            eraseCollidedArrow(&boxPtr[i]);
            pixel_buffer_start = *(pixel_ctrl_ptr + 1);
            removeBox(&boxPtr, i);
            block_flag = true;
            block_reset = true;
        }
    }
}

int checkUserInput() {
    if (coolDown > 0) {
        coolDown--;
    }
    volatile int* PS2_ptr = (int*)0xFF200100;
    int PS2_data, RVALID, RAVAIL;
    char press, pressed;
    int output;
    PS2_data = *(PS2_ptr);
    RVALID = PS2_data & 0x8000; // extract the RVALID field
    RAVAIL = PS2_data & 0xFFFF0000;


    if (RVALID)
    {
        /* save the last three bytes of data */
        press = key;
        pressed = ((press & 0xFF) == 0xF0) ? 1 : 0;
        key = PS2_data & 0xFF;

        switch (key) {
        case LEFT_ARROW: //left
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        case RIGHT_ARROW: //right
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        case UP_ARROW: //up
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        case DOWN_ARROW: //down
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));

        case A_KEY: //A key
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        case D_KEY: //D key
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        case W_KEY: //W key
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        case S_KEY: //S key
            return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        }
    }
    return 0;
}

void GameLogic(struct Box* boxPtr) {

    int inputs = checkUserInput();
    printf("\nInputs: %d, coolDown: %d\n", inputs, coolDown);
    int direction;
    if (inputs >> 8 != 0 && !coolDown) {
        direction = inputs & 0xFF;
        coolDown = 15;
        if (inputs >> 16 == 0) {
            if (direction == A_KEY)
                addBox(&boxPtr, 0);
            if (direction == D_KEY)
                addBox(&boxPtr, 1);
            if (direction == W_KEY)
                addBox(&boxPtr, 2);
            if (direction == S_KEY)
                addBox(&boxPtr, 3);
        }
        else {
            if (direction == LEFT_ARROW)
                directionFacing = 0;
            if (direction == RIGHT_ARROW)
                directionFacing = 1;
            if (direction == UP_ARROW)
                directionFacing = 2;
            if (direction == DOWN_ARROW)
                directionFacing = 3;
        }

    }
    updateAllBoxes(boxPtr);
    checkAllBoxes(boxPtr);
}