#include <avr/io.h>

void delay(unsigned long z){
	while(--z!=0);
}

int main(void)
{
	// Declaration like the Mexican border
	
	DDRC |= 0x0f; // Set the 3 digit display as output
	DDRB |= 0x07; // idk ill be honest
	
	// Turn on Mux
	
	PORTB = (PORTB & 0xf8) | 0x07; // MUX is set in binary position (0 0 0)
	while(1){
		PORTC = (PORTC & 0xf0)| 0x01; // Print the Number 1
		delay(60000);
		PORTC = (PORTC & 0xf0)| 0x02; // Print the Number 2
		delay(60000);
		PORTC = (PORTC & 0xf0)| 0x03; // Print the Number 3
		delay(60000);
	}
}
