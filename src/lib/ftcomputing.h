/**************************************/
/* ft Interface control functions     */
/**************************************/

extern void __fastcall__ ftinit();
extern void __fastcall__ ftboutp(unsigned char,unsigned char);
extern int __fastcall__ ftbinp(unsigned char);

/**************************************/
/* ft Interface control constants     */
/**************************************/

#define STOP 0b11111111
#define CW   0b01010101
#define CCW  0b10101010

#define M1 0b00000011
#define M2 0b00001100
#define M3 0b00110000
#define M4 0b11000000

#define E1 0b00000001
#define E2 0b00000010
#define E3 0b00000100
#define E4 0b00001000
#define E5 0b00010000
#define E6 0b00100000
#define E7 0b01000000
#define E8 0b10000000

#define EX 0b10100000
#define EY 0b10010000