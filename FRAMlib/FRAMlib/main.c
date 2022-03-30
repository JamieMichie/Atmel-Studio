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
	fram_status();
	fram_writeByte(0x0001, 0x55);
	
	fram_readByte(0x0001);
	
	uint8_t cmd[] = {0x11, 0x22, 0x33, 0x44, 0x55}; 
	fram_write(0x0000, cmd, (sizeof(cmd) / sizeof(uint8_t)) );
    while (1) 
    {
		
    }
}

