#include<avr/io.h>
#include<stdlib.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>

#define DDROUT	DDRB
#define	MOTOR1P	PB1
#define MOTOR1N	PB0
#define MOTOR2P	PB2
#define MOTOR2N	PB3
#define LEDOUT	PB4

#define	OUTWORD	PORTB

#define DDRIN	DDRD
#define	LED1	PD0
#define LED2	PD1
#define LED3	PD2
#define LED4	PD3
#define LED5	PD4

#define INPWORD	PIND

int main()
{
	DDROUT=(1<<MOTOR1P)|(1<<MOTOR1N)|(1<<MOTOR2P)|(1<<MOTOR2N)|(1<<LEDOUT);
	DDRIN=(0<<LED1)|(0<<LED2)|(0<<LED3)|(0<<LED4)|(0<<LED5);
	
	if(INPWORD==0xFF)
	{
		OUTWORD=(1<<LEDOUT);
	}
	
	return 0;
}




