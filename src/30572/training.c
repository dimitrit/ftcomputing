
/*
 * ==== TRAINING ROBOT --- 30572 ====
 *
 * This program requires the motors and buttons to be connected as per the diagram
 * on page 91 of the Training Robot (30572) construction manual.
 *
 *     Motor | End Switch | Pulse Counter
 *     ------+------------+--------------
 *       M1  |     E1     |      E2
 *       M2  |     E3     |      E4
 *       M3  |     E5     |      E6
 *       M4  |     E7     |      -
 *
 * Note that the 'Emergency Stop' button merely cuts +5V power to the buttons and
 * pulse detectors. E8 is left unconnected!
 *
 * The 'right' rotational direction for each of the 4 motors moves the respective axis
 * towards the start position, ie. towards to end switch. If required, swap the motor
 * connections.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "ftcomputing.h"
#include "training.h"

int main (void) {
	unsigned char ssc; // saved steps counter
	unsigned char cid; // current motor id
	unsigned int n, v; // parsed value
	int s;

	motor_t motors[4] = {
		{M1, E2, E1, 0, 1000},
		{M2, E4, E3, 0, 1000},
		{M3, E6, E5, 0, 1000},
		{M4,  0, E7, 0, 0x7fff}
	};

	cputs("\n\rft Training Robot 30572\n\r");

	ftinit();

	calibrate();

	help();

	cid = ssc = 0;

	while(1) {
		cputs("\n\rM");
		cputc('1' + cid);
		cputc(':');

		cgets(buf, 10);

		n = strlen(buf);
		v = getval(buf, n);

		switch (buf[0]) {
		case 'R':
			// if (cid == 3) {
			// 	move(motors[cid].mtr, CW, motors[cid].end, 0);
			// } else {
				/* Turn current motor right */
				s = motors[cid].cs - v;
				if (s < 0) {
					v = motors[cid].cs;
				}
				n = moveto(motors[cid].mtr, motors[cid].pulse, CW, v);
				motors[cid].cs = motors[cid].cs - n;
			// }
			break;
		case 'L':
			// if (cid == 3) {
			// 	move(motors[cid].mtr, CCW, motors[cid].end, 1);
			// } else {
				/* Turn current motor left */
				if (motors[cid].cs + v > motors[cid].ms) {
					v = motors[cid].ms - motors[cid].cs;
				}
				n = moveto(motors[cid].mtr, motors[cid].pulse, CCW, v);
				cputhex8(n);
				motors[cid].cs = motors[cid].cs + n;
			// }
			break;
		case 'S':
			/* Save position of current motor */
			cputs("\n\rSaving[");
			cputhex8(ssc);
			cputs("] M");
			cputc(cid+'1');
			cputc('@');
			cputhex8(motors[cid].cs);

			saved[ssc].id = cid;
			saved[ssc].ts = motors[cid].cs;
			ssc += 1;
			break;
		case 'P':
			/* Replay saved positions */
			cputs("\n\rReplaying");
			calibrate();
			for (s=0; s < ssc; s++) {
				cputc('.');
				replay(s);
			}
			break;
		case 'N':
			/* Reset all the things */
			calibrate();
			cid = ssc = 0;
			break;
		case 'M':
			/* Set current motor id , if possible */
			if (v > 0 && v < 5) {
				cid = v - 1;
			}
			break;
		case 'X':
			exit(0);
		default:
			help();
			break;
		}
	}
}

/* replay */
void replay(unsigned char s) {
	int df; /* step difference between current and previous */
	unsigned char id, dir;

	id = saved[s].id;

	if (s == 0) {
		df = saved[s].ts - motors[id].cs;
	} else {
		df = saved[s].ts - saved[s-1].ts;
	}
	if (df<0) {
		dir = CW;
		df = -df;
	} else {
		dir = CCW;
	}
	moveto(motors[id].mtr, motors[id].pulse, dir, df);
}

/* Moves all 4 motors to their starting position */
void calibrate() {
	unsigned char i;

	for (i=0; i<4; i++){
		cputs("\n\rCalibrating M");
		cputc(i+'1');

		if (ftbinp(motors[i].end)) {
			move(motors[i].mtr, CW, motors[i].end, 0);
		}

		motors[i].cs = 0;
		if (i < 3) {
			moveto(motors[i].mtr, motors[i].pulse, CCW, 1);
		}
	}
	motors[3].cs= 0x4000;

	cputs("\n\rReady!\n\r");
}

/*
   Moves the given motor in direction until the button is depressed.
*/
void move(unsigned char mtr, unsigned char dir, unsigned char btn, unsigned char onoff) {
	/* wait for button press */
	while (onoff ^ ftbinp(btn)) {
		ftboutp(mtr, dir);
	}
	/* now stop motor */
	ftboutp(mtr, STOP);
}

unsigned int strlen(char* buf){
	int i=0;
	while (buf[i] != 0) {
		++i;
	}
	return i;
}

unsigned int getval(char* buf, char len){
	unsigned char i;
	unsigned int c;

	c=0;

	for (i=1; i<len; i++){
		if(buf[i]>'/' && buf[i]<':') {
			c = c * 10 + (buf[i]-48);
		}
	}

	return c;
}

void help() {
	cputs("\n\rInstructions:\n\rMn - select motor n");
	cputs("\n\rRn - rotate current motor n steps right");
	cputs("\n\rLn - rotate current motor n steps left");
	cputs("\n\rS  - save current position");
	cputs("\n\rP  - replay saved positions");
	cputs("\n\rN  - clear saved positions");
	cputs("\n\rX  - exit\n\r");
}
