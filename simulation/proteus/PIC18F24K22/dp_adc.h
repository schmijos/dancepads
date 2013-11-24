#ifndef DP_ADC_H
#define DP_ADC_H

static const unsigned short adc_max = 0x3FFF;

void adc_initialize();
unsigned short adc_busy_read();

#endif // DP_ADC_H
