#define HIGH          0xFFFFFF
#define LOW           0x000000
#define FIFOFREQUENCY 8000
#define LOWERLIM      100
#define UPPERLIM      2000
#define DISCIPATIONK  0.6

int echoSamplesNum = (FIFOFREQUENCY * 2) / 5; // Echo Delay of 0.4 seconds avoids errors we get from doubles.
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

int getAudioIn(){
    int fifoSpace, signal;
    while(1){
        fifoSpace = *(AudioBase + 1) & 0x0FF; // we only read from microphone right channel
        if((fifoSpace > 32) || (fifoSpace == 0x80000000)){
            signal = *(AudioBase + 3);
            return signal;
        }
    }
    
}

void writeToAudio(int signal){
    int fifoSpace;
    while(1){
        fifoSpace = *(AudioBase + 1) & 0xFF000000;
        if((fifoSpace > 0x20000000) || (fifoSpace == 0x80000000)){
            *(AudioBase + 2) = signal;
            *(AudioBase + 3) = signal;
            return;
        }
    }
}

int main(){
    
    int echoSamples[echoSamplesNum];
    while(1){
        for(int i = 0; i < echoSamplesNum; i++){
            echoSamples[i] = getAudioIn() + echoSamples[i]*DISCIPATIONK;
            writeToAudio(echoSamples[i]);
        }
    }
}