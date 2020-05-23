/*
 * File:   main.c
 * Author: Hossam Eldeen Altokhy
 *
 * Created on May 16, 2020, 9:33 AM
 */

#define F_CPU 8000000UL

#define SS      4
#define MOSI    5
#define MISO    6
#define SCK     7

#include <xc.h>
#include <avr/interrupt.h>
#include <string.h>
void SPI_Slave_init() {
    // Data Direction Configuration
    DDRB |= (1 << MISO);
    SPCR |= (1 << SPE) | (1 << SPR1) | (1 << SPR0); //| (1 << SPIE);
}

//ISR(SPI_STC_vect) {
//    PORTD = SPDR;
//
//    SPDR = 0;
//}
unsigned char data;

int main(void) {
    /* Replace with your application code */
    DDRC = 0xFF;

    SPI_Slave_init();
    //    sei();
    while (1) {
        if(checkData('\0')){
            // True
            PORTC = data;
        }
        else{
            // False
        }
        
    }
}

char SPI_read() {
    while (!(SPSR & (1 << SPIF)));
    data = SPDR; // Signed value
    return data;
}

void SPI_readString(char *buffer) {
    //    char buffer[20]; // Local
//    char dataSize = SPI_read();
//    dataSize -= 48;
//    for (int i = 0; i < dataSize; i++) {
//        buffer[i] = SPI_read();
//        //        *(buffer+i) = SPI_read();
//    }
     for (int i = 0; SPI_read()!= 32; i++) {
        buffer[i] = SPI_read();
        //        *(buffer+i) = SPI_read();
    }
}
//"Hello "
//"5Hello"
//"3Ali"
int checkData(char *cmpStr) {
    char buffer[20];
    SPI_readString(buffer);
    int flag = strcmp(buffer,cmpStr);
    return flag==0? 1: 0;
}