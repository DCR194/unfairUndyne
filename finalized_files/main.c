
#include "gameLogic.h"
#include "userOutput.h"



key = OFF;
coolDown_time = COOLDOWN_TIMER_EASY;

int main() {

    //WHERE LEGENDS COOK
    while (1) {
        int menuPosition = MENU_START;

        while (1) { // MENU LOOP
            
            int defenderInput = checkUserInput();
            if (defenderInput >> 8 != OFF && defenderInput >> 16 == DEFENDER) {
                if (defenderInput && 0xFF == UP_ARROW || defenderInput & 0xFF == DOWN_ARROW) {
                    menuPosition = -menuPosition;
                }
            }

            if (menuPosition == MENU_START) {
                backGround = easyBG;
            }
            else {
                backGround = hardBG;
            }

            // WAIT FOR V_SYNC
            draw_background();

        }


        numBoxes = 0;
        boxPtr = NULL;
        globalTime = 0;

        while (1) { // GAME LOOP

            GameLogic();

        }
    }


    return 0;
}