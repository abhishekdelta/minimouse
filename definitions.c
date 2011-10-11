
#define MAXX    4
#define MAXY    4
#define STARTX  4
#define STARTY  4
#define DESTX   0
#define DESTY   0


#define OK 0
#define BLOCK 1
#define INVALID 2
#define PRESET  3

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define sbi(ADDRESS,BIT)  (ADDRESS |= (1<<BIT))
#define cbi(ADDRESS,BIT)  (ADDRESS &= ~(1<<BIT))



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

