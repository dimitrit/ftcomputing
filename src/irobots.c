#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "ftcomputing.h"

void move(unsigned char mtr, unsigned char dir);
void delay(unsigned int count);

typedef struct {
	unsigned char mtr;	// motor
	unsigned char pulse;	// pulse button
	unsigned char end;	// end button
	unsigned int cs;	// current step
	unsigned int ms;	// max steps
} motor_t;

motor_t motors[4] = {
	{M1, E2, E1, 0, 100},
	{M2, E4, E3, 0, 100},
	{M3, E6, E5, 0, 100},
	{M4, E8, E7, 0, 100}
};

int main (void) {
	unsigned char c, i;

	ftinit();

	cputs("\n\rft Industry Robots");

	for (i=0; i<4; i++){
		cputs("\n\rCalibrating M");
		cputc(i+'1');
		while(ftbinp(motors[i].end) == 0) {
			cputc('.');
			move(motors[i].mtr, CCW);
		}
	}

	cputs("\n\rReady!\n\r");

	i = 0;

	while(1) {
		c = cgetc();
		switch (c)
		{
		case 'L':
			cputc(c);
			move(i,CCW);
			break;
		case 'R':
			cputc(c);
			move(i,CW);
			break;
		default:
			if (c>'0' && c <'5') {
				cputs("\n\rUsing M");
				cputc(c);
				cputc(':');
				i = motors[c-'1'].mtr;
			}
			break;
		}
	}
}

void move(unsigned char mtr, unsigned char dir) {
	ftboutp(mtr, dir);

	delay(500);

	ftboutp(mtr, STOP);
}

void delay(unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; ++i) {
        __asm__("nop"); // Keep loop from being optimized out
    }
}