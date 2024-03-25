#include <stdio.h>
#include <stdlib.h> 


struct Box {
    int xPos;
    int yPos;
    int xDir;
    int yDir;
};


void printBox(struct Box* box);
void removeBox(struct Box** boxPtr, int* numBoxes, int index);
void setBoxValues(struct Box* box, int direction);
void updatePosition(struct Box* box);
void addBox(struct Box** boxPtr, int* numBoxes, int direction);

int main() {
    int numBoxes = 0;
    struct Box* boxPtr = NULL;

    // Example usage of addBox function to create 3 boxes
    addBox(&boxPtr, &numBoxes, 0);
    addBox(&boxPtr, &numBoxes, 0);
    addBox(&boxPtr, &numBoxes, 0);

    // Set the values of boxPtr[0] to all 0s, boxPtr[1] to all 1s, and boxPtr[2] to all 2s
    for (int i = 0; i < numBoxes; i++) {
        struct Box* currentBox = &boxPtr[i];
        currentBox->xPos = i;
        currentBox->yPos = i;
        currentBox->xDir = i;
        currentBox->yDir = i;
    }

    // Print the info of all the boxes
    printf("Boxes before updates:\n");
    for (int i = 0; i < numBoxes; i++) {
        printf("Box %d:\n", i);
        printBox(&boxPtr[i]);
    }

    // Update boxPtr[0] once, boxPtr[1] twice, and boxPtr[2] three times
    boxPtr[0].xPos += 1;
    boxPtr[1].xPos += 2;
    boxPtr[1].yPos += 2;
    boxPtr[2].xPos += 3;
    boxPtr[2].yPos += 3;

    // Print the updated boxes
    printf("\nBoxes after updates:\n");
    for (int i = 0; i < numBoxes; i++) {
        printf("Box %d:\n", i);
        printBox(&boxPtr[i]);
    }

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
    printf("xPos: %d, yPos: %d, xDir: %d, yDir: %d",
        box->xPos, box->yPos, box->xDir, box->yDir);
}

// Function to remove the first box (FIFO)
void removeBox(struct Box** boxPtr, int* numBoxes, int index) {
    // Check if the index is valid
    if (index < 0 || index >= *numBoxes) {
        printf("Invalid index\n");
        return;
    }

    // Free the memory occupied by the box at the specified index
    free(&(*boxPtr)[index]);

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