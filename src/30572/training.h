
typedef struct {
	unsigned char mtr;	// motor
	unsigned char pulse;	// pulse button
	unsigned char end;	// end button
	unsigned int cs;	// current step
	unsigned int ms;	// max steps
} motor_t;

typedef struct {
	unsigned char id;	// id of motor
	int ts;			// target step
} step_t;

motor_t motors[4] = {
	{M1, E2, E1, 0, 1000},
	{M2, E4, E3, 0, 1000},
	{M3, E6, E5, 0, 1000},
	{M4,  0, E7, 0, 0}
};

step_t saved[80];
char buf[10];

void help();
/* Display help text */

void replay(unsigned char s);

unsigned int strlen(char* buf);
/* Returns lenght of the string pointed to by buf */

unsigned int getval(char* buf, char len);
/* Parse string for integer value, returns 0 if no number was parsed */

void calibrate();
/* Calibrate the robot arm by moving all motors to their initial position */

void move(unsigned char mtr, unsigned char dir, unsigned char btn, unsigned char onoff);
/* Move the motor in the given direction until the button is pressed */

extern unsigned int __fastcall__ moveto(unsigned char mtr, unsigned char ctr, unsigned char dir, unsigned int steps);
/* Move the motor the number of steps in the direction using the pulse counter, returns actual steps */
