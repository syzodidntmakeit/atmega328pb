#include <avr/io.h>

void delay(unsigned long z)
{
	while(--z!=0);
}

int main(void)
{
    DDRD = 0xff; // Set all PORTD to output
	while(1)
	{
		PORTD = 0x3f; // 0
		delay(500000);
		PORTD = 0x06; // 1
		delay(500000);
		PORTD = 0x5b; // 2
		delay(500000);
		PORTD = 0x4F; // 3
		delay(500000);
		PORTD = 0x66; // 4
		delay(500000);
		PORTD = 0x6D; // 5
		delay(500000);
		PORTD = 0x7D; // 6
		delay(500000);
		PORTD = 0x07; // 7
		delay(500000);
		PORTD = 0xff; // 8
		delay(500000);
		PORTD = 0x6F; // 9
		delay(500000);
	}
}
