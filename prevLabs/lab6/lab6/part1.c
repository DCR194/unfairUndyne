volatile int *KEYedge =  0xFF20005C;
volatile int *LEDR_ptr = 0xFF200000;

void writeLEDS(int ledValue){
    if(ledValue){
        *LEDR_ptr = 0x3FF;
        *KEYedge = 0x01;
    }else{
        *LEDR_ptr = 0x000;
        *KEYedge = 0x2;
    }
}

int main()
{
    int value;

    while (1){
        value = *KEYedge & 0x01;
        if(value != 0){
            writeLEDS(1);
        }

        value = *KEYedge & 0x2;
        if(value != 0){
            writeLEDS(0);
        }

    }
    return 0;
}
