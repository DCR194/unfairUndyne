#include <stdio.h>
#include <stdlib.h> 
#include "boxLogic.h"

int numBoxes = 0;
int directionFacing = 0;
struct Box* boxPtr = NULL;


int main() {

    // Example usage of addBox function to create 3 boxes
    addBox(&boxPtr, 0);
    addBox(&boxPtr, 1);
    addBox(&boxPtr, 2);

    

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

    printf("\nboxPtr[0] before moving to shield\n");
    printBox(&boxPtr[0]);
    int iterations = 0;
    while (checkHitbox(&boxPtr[0]) == 0) { 
      updatePosition(&boxPtr[0]);
      iterations += 1;
    }
    printf("\nboxPtr[0] after moving to shield %d after %d iterations\n", checkHitbox(&boxPtr[0]), iterations);
    printBox(&boxPtr[0]);

  

    printf("\nboxPtr[1] before moving to shield\n");
    printBox(&boxPtr[1]);
    iterations = 0;
    while (checkHitbox(&boxPtr[1]) == 0) { 
      updateAllBoxes(boxPtr);
      iterations += 1;
    }
    printf("\nboxPtr[1] after moving to shield %d after %d iterations\n", checkHitbox(&boxPtr[1]), iterations);
    printBox(&boxPtr[1]);



    printf("\nboxPtr[2] before moving to shield\n");
    printBox(&boxPtr[2]);
    iterations = 0;
    while (checkHitbox(&boxPtr[2]) == 0) {
        updatePosition(&boxPtr[2]);
        iterations += 1;
    }
    printf("\nboxPtr[2] after moving to shield %d after %d iterations\n", checkHitbox(&boxPtr[2]), iterations);
    printBox(&boxPtr[2]);



    // Remove boxPtr[1]

    // Print all remaining boxes
    printf("\nBoxes pre remove:\n");

    printBox(&boxPtr[0]);
    printBox(&boxPtr[1]);
    printBox(&boxPtr[2]);
    removeBox(&boxPtr, 1);

    printf("\nBoxes after removing box[1]:\n");
    printBox(&boxPtr[0]);
    printBox(&boxPtr[1]);
  
    removeBox(&boxPtr, 0);
    printf("Removed 0th box\n");
    printBox(&boxPtr[0]);
    
  
    removeBox(&boxPtr, 0);
    printf("Remove done\n");

    return 0;
}