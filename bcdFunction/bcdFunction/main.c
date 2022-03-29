/*
 * bcdFunction.c
 *
 * Created: 23/03/2022 08:00:17
 * Author : SS7U9741
 */ 

#include <avr/io.h>

uint8_t* chartobcd(const char *timestring);
void fizzbuzz(uint16_t number);

uint8_t* chartobcd(const char *timestring){
	
	/* Time Format HHMMSS */ 
}

void fizzbuzz(uint16_t number){
	for(int i = 0; i < number; i++){
		if(!(i % 3)){
			//print Fizz
			PORTB |= (1 << PB1);
		}else if(!(i % 5)){
			PORTB |= (1 << PB1);
		}else if(!(i % 3) && (i % 5)){
			PORTB |= (1 << PB1);
		}
	}	
}
int main(void)
{
    /* Replace with your application code */
//	const char timeVar[] = {"095519"};
//	chartobcd(timeVar);
	fizzbuzz(65000);
    while (1) 
    {
    }
}

