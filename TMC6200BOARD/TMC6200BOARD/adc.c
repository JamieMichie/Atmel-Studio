/*
 * ADC.c
 *
 * Created: 17/07/2020 19:39:44
 *  Author: Jamie
 */ 

#include "sam.h"
#include "printf.h"
#define NVM_READ_CAL(cal) \
((*((uint32_t *)NVMCTRL_OTP4 + NVM_##cal##_POS / 32)) >> (NVM_##cal##_POS % 32)) & ((1 << NVM_##cal##_SIZE) - 1)

void adcInit(uint8_t resolution){
		/*
	PB00 - AIN[8]
	PB01 - AIN[9]
	PB02 - AIN[10]
	MUXB
	*/
	PM->APBCMASK.bit.ADC_ = 1;
	
	/*PORT->Group[1].PINCFG[0].bit.INEN = 1; 
	PORT->Group[1].PINCFG[1].bit.INEN = 1;
	PORT->Group[1].PINCFG[2].bit.INEN = 1;
	PORT->Group[1].PINCFG[8].bit.INEN = 1; //AIN2 
	*/
	
	PORT->Group[1].PINCFG[0].bit.PMUXEN = 1;
	PORT->Group[1].PINCFG[1].bit.PMUXEN = 1;
	PORT->Group[1].PINCFG[2].bit.PMUXEN = 1;
	PORT->Group[1].PINCFG[4].bit.PMUXEN = 1;
	
	PORT->Group[1].PMUX[0].bit.PMUXE = PORT_PMUX_PMUXE_B_Val;
	PORT->Group[1].PMUX[0].bit.PMUXO = PORT_PMUX_PMUXO_B_Val;
	PORT->Group[1].PMUX[1].bit.PMUXE = PORT_PMUX_PMUXE_B_Val;
	PORT->Group[1].PMUX[4].bit.PMUXE = PORT_PMUX_PMUXE_B_Val;
	
	ADC->CTRLB.bit.PRESCALER = ADC_CTRLB_PRESCALER_DIV32_Val;
	ADC->REFCTRL.reg = ADC_REFCTRL_REFSEL_INTVCC1 | ADC_REFCTRL_REFCOMP;
	ADC->CTRLB.reg = ADC_CTRLB_CORREN;
	ADC->CTRLB.reg = ADC_CTRLB_RESSEL_16BIT ;
	ADC->REFCTRL.reg = ADC_REFCTRL_REFSEL_INTVCC1_Val;
	ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_128;
	ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXPOS_PIN8_Val | ADC_INPUTCTRL_MUXNEG_GND_Val ;
	ADC->CALIB.reg = ADC_CALIB_BIAS_CAL(ADC_CALIB_BIAS_CAL_Msk) | ADC_CALIB_LINEARITY_CAL(ADC_CALIB_LINEARITY_CAL_Msk);

	ADC->CTRLA.reg = ADC_CTRLA_ENABLE;
	ADC->SWTRIG.bit.START = 1; // start Conversion
}

void adcRead(void){
	
	while(!(ADC->INTFLAG.reg & ADC_INTENCLR_RESRDY)){};
	uint16_t adcResult = (ADC->RESULT.reg);
	printf("AIN2 : %d \r\n", adcResult);
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
}

void adcReadAll(void){
	
	uint16_t adcResult = 0;
	ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXPOS_PIN8_Val | ADC_INPUTCTRL_MUXNEG_GND_Val ;
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	while(!(ADC->INTFLAG.reg & ADC_INTENCLR_RESRDY)){};
	adcResult = ADC->RESULT.reg;
	
	//disguard first result
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	while(!(ADC->INTFLAG.reg & ADC_INTENCLR_RESRDY)){};
	adcResult = ADC->RESULT.reg;
	
	printf("AIN8 : %4d \r\n", adcResult);
	
	ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXPOS_PIN9_Val | ADC_INPUTCTRL_MUXNEG_GND_Val ;
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	while(!(ADC->INTFLAG.reg & ADC_INTENCLR_RESRDY)){};
	adcResult = ADC->RESULT.reg;
	
	//disguard first result
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	while(!(ADC->INTFLAG.reg & ADC_INTENCLR_RESRDY)){};
	adcResult = ADC->RESULT.reg;
	
	printf("AIN9 : %4d \r\n", adcResult);
	
	ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXPOS_PIN10_Val | ADC_INPUTCTRL_MUXNEG_GND_Val ;
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	while(!(ADC->INTFLAG.reg & ADC_INTENCLR_RESRDY)){};
	adcResult = ADC->RESULT.reg;
	
	//disguard first result
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	while(!(ADC->INTFLAG.reg & ADC_INTENCLR_RESRDY)){};
	adcResult = ADC->RESULT.reg;
	
	printf("AIN10: %4d \r\n", adcResult);
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
}