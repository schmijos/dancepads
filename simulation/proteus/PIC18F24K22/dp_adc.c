#include "dp_adc.h"

#include <p18cxxx.h>
#include <adc.h>
#include <delays.h>

void adc_initialize()
{
    // Konfiguration des ADC
    OpenADC ( 
        ADC_FOSC_16 & ADC_RIGHT_JUST & ADC_4_TAD, // ADC_4_TAD = Converting over 4*(1/(FOSC/16)) = 4*(1/250kHz) = 16us
        ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS, // FOSC = 4 MHz
        0b0000000000000001 // wieso geht ADC_1ANA nicht?
    );
}

unsigned short adc_busy_read()
{
    unsigned short result;

    // Beginn der A->D Umsetzung
    ConvertADC();
 
    // Warten bis die Umsetzung fertig ist
    while( BusyADC() );
    
    // Das Ergebnis in "result" speichern
    return ReadADC();
}

