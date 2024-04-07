#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "boxLogic.h"
#include "userInput.h"

//COOLDOWN SHOULD BE INITIALIZED AS NON ZERO
extern int coolDown;
void GameLogic() {

    // INPUT FORMATTED AS: BYTE1, BYTE2, BYTE3
    // BYTE1 is either 0 or 1 to indicate if player 1 uses WASD or player 2 uses arrow keys
    // BYTE2 indicated if the key is held down at that instant
    // BYTE3 is the key value
    // Example 00016B: player 2 is using arrow keys, currently held down arrow key, and the key is left (6B)
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