#ifndef USER_INPUT_C
#define USER_INPUT_C

#define LEFT_ARROW 0x6B
#define RIGHT_ARROW 0x74
#define UP_ARROW 0x75
#define DOWN_ARROW 0x72
#define W_KEY 0x1D
#define A_KEY 0x1C
#define S_KEY 0x1B
#define D_KEY 0x23

#include <stdio.h>
#include <stdlib.h>


int checkUserInput() {

    volatile int * PS2_ptr = (int *)0xFF200100;
    int PS2_data, RVALID, RAVAIL;
    char key = 0;
    char press, pressed;
    int output;
    PS2_data = *(PS2_ptr);
        RVALID = PS2_data & 0x8000; // extract the RVALID field
        RAVAIL = PS2_data & 0xFFFF0000;
  
  
        if (RVALID)
        {
            /* save the last three bytes of data */
            press = key;
            pressed = ((press&0xFF) == 0xF0)? 1 : 0;
            key = PS2_data & 0xFF;
  
            switch (key) {
                case LEFT_ARROW: //left
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case RIGHT_ARROW: //right
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case UP_ARROW: //up
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case DOWN_ARROW: //down
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        
                case A_KEY: //A key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case D_KEY: //D key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case W_KEY: //W key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case S_KEY: //S key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
            }        
        }
    return 0;
}

#endif