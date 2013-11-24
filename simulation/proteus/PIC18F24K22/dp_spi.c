#include "dp_spi.h"

#include <p18cxxx.h>

// Documentation: http://www.jgorasia.com/Files/UBWdemos/Documentation/periph-lib/SPI.htm
// PIC Tutorials: http://sprut.de/electronic/pic/programm/index.htm

void spi_initialize()
{
        //SSPSTAT &= 0x3F; // power on state
        //SSPCON1 = 0x00; // power on state

        //SSPCON1 |= 4; // select serial mode: slave mode w /SS enable
        //SSPSTAT |= smp_phase; // select data input sample phase

        TRISAbits.TRISA5 = 1; // /SS as input
        TRISCbits.TRISC3 = 1; // clock as input;

        TRISCbits.TRISC4 = 1; // define SDI pin as input
        TRISCbits.TRISC5 = 0; // define SDO pin as output

        OpenSPI1(SLV_SSON, MODE_11, SMPMID);
}

uint8_t spi_readWord()
{
//        uint16_t word=0b1111110000000000;
//        uint16_t word=0b0111110000000000;

        uint8_t word=0;
        word += ReadSPI1();
        //word <<=8;
        //word += ReadSPI1();

        return word;
}


