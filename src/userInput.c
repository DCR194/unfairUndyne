#include <stdlib.h>
#include <stdio.h>
void HEX_PS2(char, char, char);

int main() {
	volatile int * PS2_ptr = (int *)0xFF200100;
	int PS2_data, RVALID, RAVAIL;
	char key = 0;
	char press, pressed;
	int output;
	while (1) {
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
              case 0x6B: //left
				if (pressed) {
                	HEX_PS2(0, pressed, key);
				}
				else {
					HEX_PS2(0, pressed, key);
				}
                break;
              case 0x74: //right
				if (pressed) {
                	HEX_PS2(0, pressed, key);
				}
				else {
					HEX_PS2(0, pressed, key);
				}
                break;
              case 0x75: //up
                if (pressed) {
                	HEX_PS2(0, pressed, key);
				}
				else {
					HEX_PS2(0, pressed, key);
				}
                break;
              case 0x72: //down
                if (pressed) {
                	HEX_PS2(0, pressed, key);
				}
				else {
					HEX_PS2(0, pressed, key);
				}
                break;

              case 0x1C: //A key
                if (pressed) {
                	HEX_PS2(1, pressed, key);
				}
				else {
					HEX_PS2(1, pressed, key);
				}
                break;
              case 0x23: //D key
                if (pressed) {
                	HEX_PS2(1, pressed, key);
				}
				else {
					HEX_PS2(1, pressed, key);
				}
                break;
              case 0x1D: //W key
                if (pressed) {
                	HEX_PS2(1, pressed, key);
				}
				else {
					HEX_PS2(1, pressed, key);
				}
                break;
              case 0x1B: //S key
				if (pressed) {
                	HEX_PS2(1, pressed, key);
				}
				else {
					HEX_PS2(1, pressed, key);
				}
                break;
            }        
        }
	}
}




/****************************************************************************************
* Subroutine to show a string of HEX data on the HEX displays
****************************************************************************************/
void HEX_PS2(char b1, char b2, char b3) {
	volatile int * HEX3_HEX0_ptr = (int *)0xFF200020;
	volatile int * HEX5_HEX4_ptr = (int *)0xFF200030;
	/* SEVEN_SEGMENT_DECODE_TABLE gives the on/off settings for all segments in
	* a single 7-seg display in the DE1-SoC Computer, for the hex digits 0 - F
	*/
	unsigned char seven_seg_decode_table[] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
		0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	unsigned char hex_segs[] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned int shift_buffer, nibble;
	unsigned char code;
	int i;
	shift_buffer = (b1 << 16) | (b2 << 8) | b3;
	for (i = 0; i < 6; ++i) {
		nibble = shift_buffer & 0x0000000F; // character is in rightmost nibble
		code = seven_seg_decode_table[nibble];
		hex_segs[i] = code;
		shift_buffer = shift_buffer >> 4;
	}
	/* drive the hex displays */
	*(HEX3_HEX0_ptr) = *(int *)(hex_segs);
	*(HEX5_HEX4_ptr) = *(int *)(hex_segs + 4);
}
