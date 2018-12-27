#include <avr/io.h>
#define F_CPU 1000000UL
//#include <util/delay.h>
#include <util/delay_basic.h>

void pause100()
{
	_delay_loop_2(25000);
}

void pause200()
{
	_delay_loop_2(50000);
}

void pause300()
{
	_delay_loop_2(50000);
	_delay_loop_2(25000);
}

void pause500()
{
	_delay_loop_2(50000);
	_delay_loop_2(50000);
	_delay_loop_2(25000);
}

void pause1000()
{
	pause500();
	pause500();
}

typedef struct {
uint8_t number;
uint8_t repeat;
uint8_t delay;
uint8_t pattern;
} order;

order orders[]={
{2,4,10,0b111111},
{1,1,10,0b0},


{5,9,3,0b001001},
{1,1,3,0b010010},
{1,1,3,0b100100},
{1,1,3,0b010010},
{1,1,3,0b001001},

{5,9,2,0b001001},
{1,1,2,0b010010},
{1,1,2,0b100100},
{1,1,2,0b010010},
{1,1,2,0b001001},

{2,5,2,0b111111},
{1,1,2,0b0},

{5,9,3,0b100100},
{1,1,3,0b010010},
{1,1,3,0b001001},
{1,1,3,0b010010},
{1,1,3,0b100100},

{5,9,2,0b100100},
{1,1,2,0b010010},
{1,1,2,0b001001},
{1,1,2,0b010010},
{1,1,2,0b100100},


{4,5,3,0b111000},
{1,1,3,0b0},
{1,1,3,0b000111},
{1,1,3,0b0},

{4,5,3,0b111000},
{1,1,3,0b111111},
{1,1,3,0b000111},
{1,1,3,0b0},


{5,9,3,0b110110},
{1,1,3,0b101101},
{1,1,3,0b011011},
{1,1,3,0b101101},
{1,1,3,0b110110},

{5,9,2,0b110110},
{1,1,2,0b101101},
{1,1,2,0b011011},
{1,1,2,0b101101},
{1,1,2,0b110110},

{2,5,2,0b111111},
{1,1,2,0b0},

{5,9,3,0b011011},
{1,1,3,0b101101},
{1,1,3,0b110110},
{1,1,3,0b101101},
{1,1,3,0b011011},

{5,9,2,0b011011},
{1,1,2,0b101101},
{1,1,2,0b110110},
{1,1,2,0b101101},
{1,1,2,0b011011},


{2,5,2,0b111111},
{1,1,2,0b0},

{2,9,1,0b111111},
{1,1,1,0b0},

{1,3,10,0b111111},
{1,2,10,0b0},
};

void light(uint8_t bits)
{
	//PORTB = bits;
	// PORTB in input for LED on and in output+0 for LED off
	DDRB = ~bits & 0b111111;
}

void pause(uint8_t delay)
{
	switch (delay)
	{
	case 1:
		pause100();
		break;
	case 2:
		pause200();
		break;
	case 3:
		pause300();
		break;
	case 5:
		pause500();
		break;
	case 10:
		pause1000();
		break;
	default:
		pause300();
	}
}

//    DDRB = 1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3 | 1<<PB4 | 1<<PB5;
//	PORTB &= ~(1 << PB0) | ~(1 << PB1) | ~(1 << PB2) | ~(1 << PB3) | ~(1 << PB4) | ~(1 << PB5);
//	PORTB &=  ~(1 << PB2) | ~(1 << PB3) | ~(1 << PB4) | ~(1 << PB5);
//		PORTB |= (1 << PB0);
//		PORTB &= ~(1 << PB0);


int main(void)
{
//off: port out & low
//on: port out & high OR port in (tri-state)

uint16_t current;

	PORTB = 0;	// all states down
	DDRB =  1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3 | 1<<PB4 | 1<<PB5;

	while (1) {
		
		current=0;

		while (current<(sizeof(orders)/sizeof(order)))
		{
			for(int currentRepeat=0 ; currentRepeat < orders[current].repeat; currentRepeat++)
				for(int currentSubGPR=0 ; currentSubGPR < orders[current].number ; currentSubGPR++)
				{
					light(orders[current+currentSubGPR].pattern);
					pause(orders[current+currentSubGPR].delay);
				}
			current += orders[current].number;
		}
	}

	return 0;
}
