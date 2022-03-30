/*
 * FRAMlib.c
 *
 * Created: 29/03/2022 12:50:07
 * Author : SS7U9741
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"
#include "MB85RS64V.h"

int main(void)
{
    /* Replace with your application code */
	volatile uint8_t retval; 
	spi_init();
	
	fram_id();
	fram_WREN();
	fram_status();
	fram_writeByte(0x01ff, 0x45);
	fram_status();
	//fram_WRDI();
	fram_status();
	fram_readByte(0x01ff);
	
	for(uint16_t i = 0; i < FRAM_SIZE;i++){
		fram_writeByte(i, 0xAA);
	}
	
	for(uint16_t i = 0; i < FRAM_SIZE;i++){
		fram_readByte(i);
	}
	
    while (1) 
    {
		
    }
}

