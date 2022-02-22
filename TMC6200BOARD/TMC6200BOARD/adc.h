/*
 * adc.h
 *
 * Created: 17/07/2020 19:39:56
 *  Author: Jamie
 */ 


#ifndef ADC_H_
#define ADC_H_

void adcInit(uint8_t resolution);

void adcRead(void);
void adcReadAll(void);


#endif /* ADC_H_ */