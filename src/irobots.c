
/*
 * ==== KINK-ARM ROBOT --- INDUSTRY ROBOTS --- 30408 ====
 *
 * This program requires the motors and buttons to be connected as per the diagram
 * on page 36 of the Industry Robots (30408) construction manual.
 *
 *     Motor | End Switch | Pulse Counter
 *     ------+------------+--------------
 *       M1  |     E1     |      E2
 *       M2  |     E3     |      E4
 *       M3  |     E5     |      E6
 *       M4  |     E7     |      E8
 *
 * The 'left' rotational direction for each of the 4 motors moves the respective axis
 * towards the start position, ie. towards to end switch. If required, swap the motor
 * connections.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "ftcomputing.h"

void calibrate();
void move(unsigned char idx, unsigned char btn, unsigned char dir, unsigned char step);
void moveto(unsigned char idx, unsigned int step);

typedef struct {
	unsigned char mtr;	// motor
	unsigned char pulse;	// pulse button
	unsigned char end;	// end button
	unsigned int cs;	// current step
	unsigned int ms;	// max steps
} motor_t;

typedef struct {
	unsigned char mtr;
	int stp;
} step_t;

motor_t motors[4] = {
	{M1, E2, E1, 0, 0xFF},
	{M2, E4, E3, 0, 0xFF},
	{M3, E6, E5, 0, 0xFF},
	{M4, E8, E7, 0, 0xFF}
};

step_t saved[80];

int main (void) {
	unsigned char cs, c, m;
	unsigned int s;

	cputs("\n\rft Industry Robots 30408");

	ftinit();

	calibrate();

	m = cs = 0;

	while(1) {
		c = cgetc();

		switch (c) {
		case 'L':
			/* Turn current motor left */
			cputc(c);
			s = motors[m].cs - 1;
			moveto(m,s);
			break;
		case 'R':
			/* Turn current motor right */
			cputc(c);
			s = motors[m].cs + 1;
			moveto(m,s);
			break;
		case 'S':
			/* Save position of current motor */
			cputs("\n\rSaving[");
			cputhex8(cs);
			cputs("] M");
			cputc(m+'1');
			cputc('@');
			cputhex8(motors[m].cs);

			saved[cs].mtr = m;
			saved[cs].stp = motors[m].cs;
			cs += 1;
			break;
		case 'P':
			/* Replay saved positions */
			cputs("\n\rReplaying");
			for (s=0; s < cs; s++) {
				cputc('.');
				moveto(saved[s].mtr, saved[s].stp);
			}
			break;
		case 'N':
			/* Reset all the things */
			calibrate();
			m = cs = 0;
			break;
		default:
			/* Set current motor, if possible */
			if (c>'0' && c <'5') {
				cputs("\n\rUsing M");
				cputc(c);
				cputc(':');
				m = c-'1';
			}
			break;
		}
	}
}

/* Moves each of the 4 motors to their starting position */
void calibrate() {
	int i;

	for (i=0; i<4; i++){
		cputs("\n\rCalibrating M");
		cputc(i+'1');
		move(i, motors[i].end, CCW, 0);
		motors[i].cs = 0;
		moveto(i, 1);
	}

	cputs("\n\rReady!\n\r");
}

/* Moves motor with given index to the specified step position */
void moveto(unsigned char idx, unsigned int step) {
	unsigned char d;
	int s;

	if (step > motors[idx].ms) {
		step = motors[idx].ms;
	}

	if (step > motors[idx].cs) {
		d = CW;
		s = 1;
	} else {
		d = CCW;
		s = -1;
	}
	while (motors[idx].cs != step) {
		move(idx, motors[idx].pulse, d, 1);
		motors[idx].cs = motors[idx].cs + s;
	}
}

/* Moves the given motor until the relevant button is depressed. For steps, this is exactly one pulse */
void move(unsigned char idx, unsigned char btn, unsigned char dir, unsigned char step) {
	// if (motors[idx].end == 1 && dir == CCW) {
	// 	return;
	// }

	if (ftbinp(btn) && step) {
		while (ftbinp(btn)) {
			ftboutp(motors[idx].mtr, dir);
		}
	}

	ftboutp(motors[idx].mtr, STOP);

	while (!ftbinp(btn)) {
		ftboutp(motors[idx].mtr, dir);
	}

	ftboutp(motors[idx].mtr, STOP);
}