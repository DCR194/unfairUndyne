#include <stdio.h>
#include <stdlib.h> 


struct Box {
    int xPos;
    int yPos;
    int xDir;
    int yDir;
    int direction;
};


void printBox(struct Box* box);
void removeBox(struct Box** boxPtr, int index);
void setBoxValues(struct Box* box, int direction);
void updatePosition(struct Box* box);
void addBox(struct Box** boxPtr, int direction);
int checkHitbox(struct Box* boxPtr, int directionFacing);
int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);
void plot_pixel(int x, int y, short int line_color);

int numBoxes = 0;
int globalTime = 0;

int main(){
    struct Box* boxPtr = NULL;

    while(1){

    }

}


void plot_pixel(int x, int y, short int line_color) {
    volatile short int* one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = line_color;
}

void drawBox(struct Box* myBox){

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
