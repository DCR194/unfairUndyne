#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include "boxLogic.h"
#include "userInput.h"

extern int coolDown;
void GameLogic() {

    int inputs = checkUserInput();
    int direction;
    if (inputs >> 8 != 0 && !coolDown) {
        direction = inputs & 0xFF;
        if (inputs >> 16 == 0) {
            if (direction == A_KEY)
                addBox(&boxPtr, direction);
            if (direction == D_KEY)
                adBox(&boxPtr, 1);
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
  
}

#endif