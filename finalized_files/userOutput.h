#ifndef USER_OUTPUT_C
#define USER_OUTPUT_C


#include "AudioSpriteLists.h"
#include "magicNumbers.h"

extern int globalTime; //INITIALIZE AS 0
extern int numBoxes; //INITIALIZE AS 0
extern short int *backGround; //GETS SET DEPENDING ON MENU / GAME MODE

volatile int* LEDaddress = 0xFF200040;
volatile int* AudioBase = 0xFF203040;




// FIGURE OUT PIXEL BUFFER VISUALS LATER
volatile int pixel_buffer_start; // VALUE DEPENDANT ON VSYNC BEHAVIOR




bool inBounds(int x, int y);
void eraseSmartArrow(struct Box* a);
void eraseAllArrows(struct Box* boxes);
void drawSmartArrow(struct Box* a);
void writeToAudio(int audioSignal /* ADD INPUT FOR MUSIC LENGTH AND */);
int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void plot_pixel(int x, int y, short int line_color);
void draw_background();
void swap(int* a, int* b);
int abs(int a);


//ADD VSYNC FUNCTIONS LATER

bool inBounds(int x, int y) {
    return (x < XWIDTH) && (x >= 0) && (y < YHEIGHT) && (y >= 0);
}


void eraseSmartArrow(struct Box* a) {
    for (int x = 0 - abs(a->xDir); x < ARROWBOXWIDTH - abs(a->xDir); x++) {
        for (int y = 0 - abs(a->yDir); y < ARROWBOXWIDTH + abs(a->yDir); y++) {
            if (inBounds(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)),
                a->yPos + (y - (ARROWBOXWIDTH / 2) * (a->xDir / abs(a->xDir))))) {
                //if (arrowSprite[x + (y * ARROWBOXWIDTH)] != 0x0000) {
                plot_pixel(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)),
                    a->yPos + (y - (ARROWBOXWIDTH / 2)) * (a->yDir / abs(a->yDir)),
                    BLACK);
                //}
            }
        }
    }
}


void eraseAllArrows(struct Box* boxes) {
    if (numBoxes <= 0) return;
    for (int i = 0; i < numBoxes; i++) {
        if ((&boxes[i])->direction < 2) {
            eraseSmartArrow(&boxes[i]);
        }

    }
}


void drawSmartArrow(struct Box* a) { // draw the arrows but put a little thought into it
    for (int x = 0; x < ARROWBOXWIDTH; x++) {
        for (int y = 0; y < ARROWBOXWIDTH; y++) {
            if (inBounds(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)), a->yPos + y)) {
                if (arrowSprite[x + (y * ARROWBOXWIDTH)] != BLACK) {
                    plot_pixel(a->xPos + (x - (ARROWBOXWIDTH / 2)) * (a->xDir / abs(a->xDir)),
                        a->yPos + y - (ARROWBOXWIDTH / 2),
                        arrowSprite[x + (y * ARROWBOXWIDTH)]);
                }
            }
        }
    }
}


void writeToAudio(int audioSignal /* ADD INPUT FOR MUSIC LENGTH AND */) {
    int fifoSpace = *(AudioBase + 1) & 0xFF000000;

    int output;
    //SHOULD BE IN THE FORM     output = musicArray[globalArrayIdx] + audioSignal;
    
    if ((fifoSpace > 32) || (fifoSpace == 0x80000000)) {
        *(AudioBase + 2) = output;
        *(AudioBase + 3) = output;
        
        *(AudioBase + 2) = output;
        *(AudioBase + 3) = output;

        
        
        // globalArrayIdx++;
        // if(globalArrayIdx >= myArray_length){
        //     globalArrayIdx = 0;
        // }
    }
    fifoSpace = *(AudioBase + 1) & 0xFF000000;
    
}


int getSWValue() {
    return *LEDaddress;
}

int decodeHex(int value) {
    int result;
    if (value == 0) {
        result = 0b0111111;
    }
    else if (value == 1) {
        result = 0b0000110;
    }
    else if (value == 2) {
        result = 0b1011011;
    }
    else if (value == 3) {
        result = 0b1001111;
    }
    else if (value == 4) {
        result = 0b1100110;

    }
    else if (value == 5) {
        result = 0b1101101;
    }
    else if (value == 6) {
        result = 0b1111101;
    }
    else if (value == 7) {
        result = 0b0000111;
    }
    else if (value == 8) {
        result = 0b1111111;
    }
    else if (value == 9) {
        result = 0b1100111;
    }
    else { return 0; }

    return result;

}

void setSevenSegment(volatile long* segAddress, int value) {

    int seg7;

    seg7 = decodeHex(value % 10);

    value /= 10;
    seg7 += decodeHex(value % 10) << 8;

    value /= 10;
    seg7 += decodeHex(value % 10) << 16;

    value /= 10;
    seg7 += decodeHex(value % 10) << 24;

    *segAddress = seg7;
}


void draw_line(int x0, int y0, int x1, int y1, short int line_color) {
    bool is_steep = abs(y1 - y0) > abs(x1 - x0);
    if (is_steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax / 2);
    int y = y0;
    int y_step;
    if (y0 < y1) {
        y_step = 1;
    }
    else {
        y_step = -1;
    }

    for (int x = x0; x < x1; x++) {
        if (is_steep) {
            plot_pixel(y, x, line_color);
        }
        else {
            plot_pixel(x, y, line_color);
        }
        error = error + deltay;
        if (error > 0) {
            y = y + y_step;
            error = error - deltax;
        }
    }
}

void plot_pixel(int x, int y, short int line_color) {
    volatile short int* one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = line_color;
}

void draw_background() {
    int y, x;
    short int color;
    for (x = 0; x < XWIDTH; x++) {
        for (y = 0; y < YHEIGHT; y++) {
            color = backGround[x + (y * XWIDTH)];
            plot_pixel(x, y, color);
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    (*a) = (*b);
    (*b) = temp;
}

int abs(int a) {
    if (a > 0) {
        return a;
    }
    else {
        return -1 * a;
    }
}


void drawHealth(int offset) {
    for (int i=0; i<health; i++) {
        if (abs(i+offset) < 5) {
            drawMiniHeart(((2*i) + (SMALL_HEART_MEASURE*i)), (HEALTH_POSITION - abs(i + offset)));
        }
        else if (i+offset < -SMALL_HEART_MOVEMENT) {
            drawMiniHeart(((2*i) + (SMALL_HEART_MEASURE*i)), (HEALTH_POSITION - SMALL_HEART_MOVEMENT));
        }
        else if (i+offset > SMALL_HEART_MEASURE) {
            drawMiniHeart(((2*i) + (SMALL_HEART_MEASURE*i)), (HEALTH_POSITION + SMALL_HEART_MOVEMENT));
        }
    }
}

void drawMiniHeart(int x, int y) {
    for (int i = 0; i < SMALL_HEART_MEASURE; i++) {
        for (int j = 0; j < SMALL_HEART_MEASURE; j++) {
            if (miniHeartSprite[x + (y * SMALL_HEART_MEASURE)] != BLACK) {
                plot_pixel((x+i), (y+j), miniHeartSprite[x + (y * SMALL_HEART_MEASURE)]);
            }
        }
    }
}



#endif