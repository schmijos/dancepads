// Documentation: http://www.jgorasia.com/Files/UBWdemos/Documentation/periph-lib/SPI.htm
// PIC Tutorials: http://sprut.de/electronic/pic/programm/index.htm

#include "dp_spi.h"
#include <p18cxxx.h>

void spi_initialize()
{
        TRISAbits.TRISA5 = 1; // /SS as input
        TRISCbits.TRISC3 = 1; // clock as input;
        TRISCbits.TRISC4 = 1; // define SDI pin as input
        TRISCbits.TRISC5 = 0; // define SDO pin as output

        OpenSPI1(SLV_SSON, MODE_00, SMPMID);
}

// Write a byte to the SPI buffer and wait for the new one to be read
uint8_t spi_tranceive(uint8_t value)
{
  uint8_t TempVar;
  TempVar = SSP1BUF;        // clear BF
  PIR1bits.SSP1IF = 0;      // clear interrupt flag
  SSP1CON1bits.WCOL = 0;	// clear any previous write collision
  SSP1BUF = value;          // write to buffer and initiate bus cycle
    
  if ( SSP1CON1 & 0x80 )    // test if write collision occurred
   return ( 0 );            // if WCOL bit is set return negative #
  else
      
  while(!PIR1bits.SSP1IF);  // wait until cycle complete
  return ( SSP1BUF );       // return with byte read 
}
