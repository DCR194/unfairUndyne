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
void removeBox(struct Box** boxPtr, int* numBoxes, int index);
void setBoxValues(struct Box* box, int direction);
void updatePosition(struct Box* box);
void addBox(struct Box** boxPtr, int* numBoxes, int direction);
int checkHitbox(struct Box* boxPtr, int directionFacing);
void updateAllBoxes(struct Box* boxPtr, int numBoxes);

int main() {
    int numBoxes = 0;
    struct Box* boxPtr = NULL;

    // Example usage of addBox function to create 3 boxes
    addBox(&boxPtr, &numBoxes, 0);
    addBox(&boxPtr, &numBoxes, 1);
    addBox(&boxPtr, &numBoxes, 2);

    

    // Print the info of all the boxes
    printf("Boxes before updates:\n");
    for (int i = 0; i < numBoxes; i++) {
        printf("Box %d:\n", i);
        printBox(&boxPtr[i]);
    }

    // Update box positions using loops and updatePosition function
    for (int i = 0; i < numBoxes; i++) {
        for (int j = 0; j < i; j++) {
            updatePosition(&boxPtr[i]);
        }
    }

    // Print the updated boxes
    printf("\nBoxes after updates:\n");
    for (int i = 0; i < numBoxes; i++) {
        printf("Box %d:\n", i);
        printBox(&boxPtr[i]);
    }

    printf("\nboxPtr[1] before moving to shield\n");
    printBox(&boxPtr[1]);
    int iterations = 0;
    while (checkHitbox(&boxPtr[1], boxPtr[1].direction) == 0) { 
      updateAllBoxes(boxPtr, numBoxes);
      iterations += 1;
    }
    printf("\nboxPtr[1] after moving to shield %d after %d iterations\n", checkHitbox(&boxPtr[1], 1), iterations);
    printBox(&boxPtr[1]);



    printf("\nboxPtr[2] before moving to shield\n");
    printBox(&boxPtr[2]);
    iterations = 0;
    while (checkHitbox(&boxPtr[2], boxPtr[2].direction) == 0) {
        updatePosition(&boxPtr[2]);
        iterations += 1;
    }
    printf("\nboxPtr[2] after moving to shield %d after %d iterations\n", checkHitbox(&boxPtr[2], 1), iterations);
    printBox(&boxPtr[2]);



    // Remove boxPtr[1]
    removeBox(&boxPtr, &numBoxes, 1);

    // Print all remaining boxes
    printf("\nBoxes after removing boxPtr[1]:\n");
    for (int i = 0; i < numBoxes; i++) {
        printf("Box %d:\n", i);
        printBox(&boxPtr[i]);
    }

    // Delete boxPtr[0] three times
    removeBox(&boxPtr, &numBoxes, 0);

    removeBox(&boxPtr, &numBoxes, 0);
    removeBox(&boxPtr, &numBoxes, 0);

    return 0;
}



void printBox(struct Box* box) {
    printf("xPos: %d, yPos: %d, xDir: %d, yDir: %d\n", 
    box->xPos, box->yPos, box->xDir, box->yDir);
}

// Function to remove the first box (FIFO)
void removeBox(struct Box** boxPtr, int* numBoxes, int index) {
    // Check if the index is valid
    if (index < 0 || index >= *numBoxes) {
        printf("Invalid index\n");
        return;
    }

    // Shift the memory to the left to remove the box
    for (int i = index; i < *numBoxes - 1; i++) {
        (*boxPtr)[i] = (*boxPtr)[i + 1];
    }

    // Reallocate memory to decrease the size of the box array
    *boxPtr = (struct Box*)realloc(*boxPtr, (*numBoxes - 1) * sizeof(struct Box));

    // Decrement the number of boxes
    (*numBoxes)--;
}

// Function to initialize the attributes of the newest box
void setBoxValues(struct Box* box, int direction) {
    // Set position and direction values based on the direction parameter
    if (direction == 0) { //Laft
        box->xPos = 0;
        box->yPos = 119;
        box->xDir = 1;
        box->yDir = 0;
        box->direction = 0;
    }
    if (direction == 1) { //Right
        box->xPos = 319;
        box->yPos = 119;
        box->xDir = -1;
        box->yDir = 0;
        box->direction = 1;
    }
    if (direction == 2) { //Up
        box->xPos = 159;
        box->yPos = 0;
        box->xDir = 0;
        box->yDir = 1;
        box->direction = 2;
    }
    if (direction == 3) { //Down
        box->xPos = 159;
        box->yPos = 239;
        box->xDir = 0;
        box->yDir = -1;
        box->direction = 3;
    }
    // Add other conditions as needed
}

void updatePosition(struct Box* box) {
    box->xPos += box->xDir;
    box->yPos += box->yDir;
}

int checkHitbox(struct Box* boxPtr, int directionFacing) {
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
void addBox(struct Box** boxPtr, int* numBoxes, int direction) {
    // Reallocate memory to increase the size of the box array
    *boxPtr = (struct Box*)realloc(*boxPtr, (*numBoxes + 1) * sizeof(struct Box));

    // Check if memory reallocation was successful
    if (*boxPtr == NULL) {
        printf("Memory reallocation failed\n");
        return;
    }

    // Increment the number of boxes
    (*numBoxes)++;

    // Call setBoxValues to initialize the attributes of the newest box
    setBoxValues(&(*boxPtr)[*numBoxes - 1], direction);
}

void updateAllBoxes(struct Box* boxPtr, int numBoxes) {
    for (int i = 0; i < numBoxes; i++) {
        updatePosition(&boxPtr[i]);
    }
}