#include <avr/io.h>

void delay(unsigned long z){
	while(--z!=0);
}

void timerDelay(){
	TCNT1 = 0x64; // Loading counter with TCNT1
	TIFR1 = 0x01; // Clear overflow flag of TCNT1
	TCCR1B = (TCCR1B & 0xf8) | 0x04; // Start the timer using TCCR1B with 512 prescaler
	while((TIFR1 & 0x01)==0); // Wait for timer overflow
	TIFR1 |= 0x01; // Clear overflow flag again
	TCCR1B &= 0xf8; // Stop the timer
}

unsigned char lookUp(unsigned char i)	// Lookup table
{
	switch(i)
	{
		case 0: i=0x3F; break;
		case 1: i=0x06; break;
		case 2: i=0x5b; break;
		case 3: i=0x4f; break;
		case 4: i=0x66; break;
		case 5: i=0x6d; break;
		case 6: i=0x7d; break;
		case 7: i=0x7; break;
		case 8: i=0x7f; break;
		default: i=0x6f;
	}
	return(i);
}

int main(){
	unsigned char w;
	DDRD = 0xff; // Sets all of PORTD to output
	while(1){ // Run forever
		for(w=0;w<10;w++){ // Count from 0 to 9 by 1
		PORTD = lookUp(w); // Outputs PORTD of lookup table
		timerDelay();
		}
	}
}
