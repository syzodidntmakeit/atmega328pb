#include <avr/io.h>
#include <avr/interrupt.h>

void delay(unsigned long w)
{
	while(w--!=0);
}

void blink(unsigned char c)
{
	unsigned char k;
	for(k=0;k<6;k++)
	{
		PORTD ^= c;
		delay(100000);
	}
}

ISR(INT0_vect)
{
	blink(0x30);
}

ISR(INT1_vect)
{
	blink(0xc0);
}

int main(void)
{
	unsigned char x=0;
	DDRD = 0xF0;
	DDRC = 0x0F;
	DDRB = 0x07;
	PORTB |= 0x04; // MUX3 on.
	PORTD &= ~(0xF0);  // Off LEDs.
	PORTD |= 0x0C;
	// Set inputs.
	sei();  // Global Interrupt.
	EICRA |= 0x0A;
	EIMSK |= 0x03;
	// Enable interrupt.
	while(1)
	{
		PORTC= (PORTC & 0xF0) | x;
		delay(100000);
		x++;
		if (x>9) x=0;
	}
}
