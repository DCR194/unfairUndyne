#define HIGH          0xFFFFFF
#define LOW           0x000000
#define FIFOFREQUENCY 8000
#define LOWERLIM      100
#define UPPERLIM      2000
volatile int* LEDaddress = 0xFF200040;
volatile int* AudioBase =  0xFF203040;

int getSWValue(){
    return *LEDaddress;
}

int getFrequency(){
    return (getSWValue()*((UPPERLIM - LOWERLIM))/(1023)) + LOWERLIM;
}

getSamplesPerPeriod(){
    return FIFOFREQUENCY/getFrequency();
}

void writeToAudio(int signal){
    int fifoSpace = *(AudioBase + 1) & 0xFF000000;
    while(1){
        if((fifoSpace > 32) || (fifoSpace == 0x80000000)){
            *(AudioBase + 2) = signal;
            *(AudioBase + 3) = signal;
            return;
        }
        fifoSpace = *(AudioBase + 1) & 0xFF000000;
    }
}

int main(){
    int samplesPerPeriod;
    while(1){
        samplesPerPeriod =  getSamplesPerPeriod();
        for(int i = 0; i < getSamplesPerPeriod(); i++){
            writeToAudio(HIGH);
        }
        for(int i = 0; i < getSamplesPerPeriod(); i++){
            writeToAudio(LOW);
        }
    }
}