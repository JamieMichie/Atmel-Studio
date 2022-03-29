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
    while (1) 
    {
		
    }
}

