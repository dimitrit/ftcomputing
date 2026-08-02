/*
 *
 * fischertechnik computing
 *
 * Diagnostic Program
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "ftcomputing.h"

void mstat(unsigned char idx, unsigned char inv);
/* print status of motor with given index using inverse text as indicated */

typedef struct {
	unsigned char mtr;
	unsigned char dir;
} status_t;

status_t motors[4] = {
	M1, STOP,
	M2, STOP,
	M3, STOP,
	M4, STOP
};

unsigned char pots[2] = {EX, EY};

unsigned char btn[10];

int main (void) {
	unsigned char i, k, x, y;
	unsigned char cur, dir;

	ftinit();

	for (i=0; i<10; i++) {
		btn[i] = 0xFF;
	}

	clrscr();

	gotoxy(1,1);
	cputs("fischertechnik Computing Diagnostics");

	gotoxy(1,3);
	cputs(" E1   E2   E3   E4   EX");

	gotoxy(1,6);
	cputs(" E5   E6   E7   E8   EY");

	gotoxy(1,9);
	cputs(" M1   M2   M3   M4");

	gotoxy(7,10);
	cputs("STOP STOP STOP");

	cur = 0;
	mstat(cur, 1);

	while (1) {
		k = kbhit();
		if (k) {
			if (k == 'X')
				break;

			/* set current motor */
			if (k > '/' && k < '5') {
				i = k - '1';
				if (cur != i) {
					mstat(cur, 0);
					cur = i;
					mstat(cur, 1);
				}
			}

			dir = motors[cur].dir;

			switch(k) {
				case 'L':
					motors[cur].dir = CCW;
					break;
				case 'R':
					motors[cur].dir = CW;
					break;
				case 'S':
					motors[cur].dir = STOP;
					break;
			}

			if (dir != motors[cur].dir) {
				mstat(cur,1);
			}
		}

		for (i=0; i<4; i++) {
			ftboutp(motors[i].mtr, motors[i].dir);
		}

		for(i=0; i<8; i++) {
			k = ftbinp(1<<i);
			if (btn[i] != k) {
				btn[i] = k;

				x = 2 + (i % 4) * 5;
				y = 4 + (i > 3) * 3;

				gotoxy(x,y);
				if (k)
					cputs(" ON");
				else
					cputs("OFF");

				gotoxy(0,0);
			}
		}

		for (i=0; i<2; i++) {
			k = ftbinp(pots[i]);
			if (btn[i+8] != k) {
				btn[i + 8] = k;

				y = 4 + i * 3;
				gotoxy(22, y);

				cputhex8(k);

				gotoxy(0,0);
			}
		}
	}
}

void mstat(unsigned char idx, unsigned char inv) {
	int x;

	x = 1 + idx * 6;
	gotoxy(x, 10);
	revers(inv);
	switch(motors[idx].dir) {
		case CW:
			cputs("CW  ");
			break;
		case CCW:
			cputs("CCW ");
			break;
		default:
			cputs("STOP");
			break;
	}
	revers(0);
}