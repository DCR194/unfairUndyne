#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "boxLogic.h"
#define SIZECUBES 5
#define XWIDTH 320
#define YHEIGHT 240




// LOGIC FUNCTIONS
void swap(int* a, int* b);


// HEX FUNCTIONS
int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);

// DRAWING FUNCTIONS
// void draw_line(int x0, int y0, int x1, int y1, short int line_color);


int globalTime = 0;

short int Buffer1[YHEIGHT][XWIDTH + 200]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[YHEIGHT][XWIDTH + 200];

volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
volatile int pixel_buffer_start;

//THESE NEED TO BE DEFINED LOCALLY TO WORK
struct Box* boxPtr = NULL;
int numBoxes = 0;
int directionFacing = 2;

int main() {

    
    addBox(&boxPtr, 0); //add a left arrow; -->
    addBox(&boxPtr, 1); // add a right arrow <--

    printf("\nnumboxes: %d\n", numBoxes);
    //addBox(&boxPtr, 0);

    //struct Box* boxPtr = NULL;
    //addBox(&boxPtr, 0);

    while (1) {

        if(numBoxes > 0){
            printBox(&boxPtr[0]);
        }
        
        if(numBoxes == 2){
            printBox(&boxPtr[1]);
        }
        //updatePosition(&boxPtr[1], 0);
        updateAllBoxes(boxPtr);
        

        // WILL FIX CHECK ALL BOXES AND REPLACE THIS PART
        if (checkHitbox(&boxPtr[0]) != 0) {
            removeBox(&boxPtr, 0);
        }
        if (checkHitbox(&boxPtr[1]) != 0) {
            removeBox(&boxPtr, 1);
        }

        printf("\nnumboxes: %d\n", numBoxes);
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


void swap(int* a, int* b) {
    int temp = *a;
    (*a) = (*b);
    (*b) = temp;
}