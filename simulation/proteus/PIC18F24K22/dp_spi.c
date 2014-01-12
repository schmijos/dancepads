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

        OpenSPI1(SLV_SSON, MODE_00, SMPMID);
}

uint8_t spi_tranceive(uint8_t value)
{
  uint8_t TempVar;
  TempVar = SSP1BUF;       //Clear BF
  PIR1bits.SSP1IF = 0;     //Clear interrupt flag
  SSP1CON1bits.WCOL = 0;			//Clear any previous write collision
  SSP1BUF = value;          // initiate bus cycle
    
  if ( SSP1CON1 & 0x80 )       // test if write collision occurred
   return ( 0 );              // if WCOL bit is set return negative #
  else
      
  while(!PIR1bits.SSP1IF); //wait until cycle complete
  return ( SSP1BUF );      // return with byte read 
}
