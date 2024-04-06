#ifndef MAJIC_NUMBERS_C
#define MAJIC_NUMBERS_C


#define SIZECUBES 5
#define XWIDTH 320
#define YHEIGHT 240
#define ARROWBOXWIDTH 16
#define LEFT_ARROW 0x6B
#define RIGHT_ARROW 0x74
#define UP_ARROW 0x75
#define DOWN_ARROW 0x72
#define W_KEY 0x1D
#define A_KEY 0x1C
#define S_KEY 0x1B
#define D_KEY 0x23

struct Box {
    int xPos;
    int yPos;
    int xDir;
    int yDir;
    int direction;
};



#endif