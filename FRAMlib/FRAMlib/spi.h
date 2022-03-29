/*
 * spi.h
 *
 * Created: 29/03/2022 13:54:06
 *  Author: SS7U9741
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>

#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_MOSI PORTB0
#define SPI_SCK  PORTB1
#define SPI_MISO PORTB2
#define SPI_CS   PORTB3

uint8_t spi_init(void);
uint8_t spi_send(uint8_t udata);
uint8_t spi_receive(uint8_t udata);


#endif /* SPI_H_ */