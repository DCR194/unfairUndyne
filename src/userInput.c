#include <stdlib.h>
#include <stdio.h>

int checkUserInput() {

    volatile int * PS2_ptr = (int *)0xFF200100;
    int PS2_data, RVALID, RAVAIL;
    char key = 0;
    char press, pressed;
    int output;
    PS2_data = *(PS2_ptr);
        RVALID = PS2_data & 0x8000; // extract the RVALID field
  
  
        if (RVALID)
        {
            /* save the last three bytes of data */
            press = key;
            pressed = ((press&0xFF) == 0xF0)? 1 : 0;
            key = PS2_data & 0xFF;
  
            switch (key) {
                case 0x6B: //left
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case 0x74: //right
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case 0x75: //up
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case 0x72: //down
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
        
                case 0x1C: //A key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case 0x23: //D key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case 0x1D: //W key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
                case 0x1B: //S key
                    return output = 0xFFFFFF & ((0x00 << 16) | (pressed << 8) | (key));
            }        
        }
    return 0;
}