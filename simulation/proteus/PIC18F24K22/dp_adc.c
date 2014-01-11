#include "dp_adc.h"

#include <p18cxxx.h>
#include <adc.h>
#include <delays.h>

void adc_initialize()
{
    /*
	// ADC
	TRISAbits.TRISA0 = 1;
	ANSELAbits.ANSA0 = 1;

	// ADC Range
	ADCON1bits.PVCFG = 0;
	ADCON1bits.NVCFG = 0;

	// ADC channel select
	ADCON0bits.CHS = 0;

	ADCON2bits.ADFM = 1;

	// ADC aqquisition time
	ADCON2bits.ACQT0 = 1;
	ADCON2bits.ACQT1 = 0;
	ADCON2bits.ACQT2 = 0;

	ADCON0bits.ADON = 1;
    */
    
    //Konfiguration des ADC
    OpenADC ( 
        ADC_FOSC_16 & ADC_RIGHT_JUST & ADC_4_TAD, // ADC_4_TAD = Converting over 4*(1/(FOSC/16)) = 4*(1/250kHz) = 16us
        ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS, // FOSC = 4 MHz
        0b0000000000000001 // wieso geht ADC_1ANA nicht?
    );
}

unsigned short adc_busy_read()
{
    unsigned short result;
    
    
    /*
	ADCON0bits.GO = 1;
	while(ADCON0bits.GO );
	
	return ADRES;
    */
    
    //Kurze Warteschleife
    //Delay10TCY(5);
 
    //Beginn der A->D Umsetzung
    ConvertADC();
 
    //Warten bis die Umsetzung fertig ist
    while( BusyADC() );
    
    //Das Ergebnis in "result" speichern
    //result = ReadADC();
    

    return ReadADC();
}

