#ifndef GAMELOGIC_H
#define GAMELOGIC_H


#include "boxLogic.h"
#include "userInput.h"

//COOLDOWN SHOULD BE INITIALIZED AS NON ZERO
extern int coolDown;
void GameLogic() {

    int inputs = checkUserInput();
    int direction;
    if (coolDown > 0) {
        coolDown--;
    }
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

#endif