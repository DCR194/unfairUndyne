#include <stdio.h>
#include <stdlib.h> 
#include "boxLogic.h"


// IN BOXLOGIC HEADER FILE THESE VARS ARE DECLARED AS EXTERNAL
int numBoxes = 0;
int directionFacing = 0;
struct Box* boxPtr = NULL;

// FOR THIS TEST I INITIALIZED THEIR VALUES SIMILAR TO HOW WE WOULD IN THE FINAL MAIN FILE


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


    // REASON THAT BOX 0 IS AT 281 IN THE OUPUT IS BECAUSE IN THE WHILE LOOP FOR 
    // BOX 1 YOU"LL NOTICE THAT UPDATE ALL IS CALLED WHICH UPDATES BOX 0 PAST THE POINT ITS SUPPOSED TO GO
    // THATS ALSO WHY IF YOU LOOK AT ITERATIONS YOU SEE THAT BACK 2 HIT THE SHIELD AT 0 ITERATIONS
    // SINCE THE UPDATE ALL WAS CALLED IN BOX 1 AND MOVED IT TO A HITBOX ZONE


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