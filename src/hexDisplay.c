#define ADDR_7SEG1 ((volatile long *) 0xFF200020)
#define ADDR_7SEG2 ((volatile long *) 0xFF200026)
volatile int* LEDaddress = 0xFF200040;
volatile int* AudioBase = 0xFF203040;

int getSWValue();
int decodeHex(int value);
void setSevenSegment(volatile long* segAddress, int value);


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


int main()
{
    //# bits 0000110 will activate segments 1 and 2 
    while (1) {
        int value, seg7;
        value = getSWValue();
        setSevenSegment(ADDR_7SEG1, value);

    }
}