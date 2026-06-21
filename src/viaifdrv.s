		;**************************************
		; PAL-2 VIA Interface Driver Program
		;**************************************
		; This driver is based on the C64 driver
		; Control of the fischertechnik Interface
		; using _ftboutp() and _ftbinp() for
		; output and input, respectively.
		; NOTE: _ftinit() must be called before
		; attempting to read buttons or control
		; motors.
		;**************************************
		; These routines require the ft interface to be
		; connected to the PAL-2 VIA I/F as following:
		;            LOAD_OUT  [8] --- PB0
		;             LOAD_IN  [7] --- PB1
		;            DATA_OUT [10] --- PB2
		;                 CLK  [9] --- PB3
		;           TRIGGER_X [11] --- PB4
		;           TRIGGER_Y [12] --- PB5
		;            COUNT_IN  [4] --- PB6
		;  	  C64_DATA_IN [18] --- PB7
		;                 GND [20] --- GND
		;              POTI_X [13] --- RC_X [15]
		;              POTI_Y [14] --- RC_Y [16]
		;
		;**************************************
		;
		;**************************************
		.include "FTCOMPUTING.INC"
		;**************************************
		; Global definitions
		;**************************************
		.export _ftinit, _ftboutp, _ftbinp
		.import popa
		.importzp tmp1
		;**************************************
		; VIA 1 Input and output registers
		;**************************************
orb		= $1600			;output register b
ddrb		= $1602			;data direction reg b
t2cl		= $1608 		;timer 2 low register
t2ch		= $1609 		;timer 2 high register
acr		= $160b 		;aux control register

PRTBYT		= $1e3b			; print two hex characters on tty

		;**************************************
		; Variables in the zero page
		;**************************************
		.segment "ZEROPAGE"
avar:		.res 1	 		;output variable
mask:		.res 1 			;mask variable
		;**************************************
		; Routines for output control
		; Call in using the SYS command
		;**************************************
		;**************************************
		; Entry point for if initialisation
		;**************************************
		.segment "CODE"
_ftinit:	sei 			;disable interrupt
		lda #$00 		;all motors off
		beq ftstvar		;branch always
		;**************************************
		; Entry point for digital output
		;**************************************
		;void __fastcall__ ftboutp(unsigned char,unsigned char);
		;**************************************
_ftboutp:	sei			;disable interrupt
		sta tmp1
		jsr popa
		sta mask		;save bit mask
		lda avar		;get previous output
		ora mask		;set both bits
		sta avar		;intermediate storage
		lda tmp1
		and mask		;mask motor
		sta mask		;intermediate storage
		lda avar		;get output variable
		eor mask		;set bit (10, 01, 00)
ftstvar:	sta avar		;save for output
		tay			;copy in y-reg
		;**************************************
		; Routine for interface control
		; Output control
		; Output bit pattern in AVAR
		; Uses A- and X-registers
		;**************************************
		lda #$3f		;set data direction
		sta ddrb		;store in register
		ldx #$08		;loop for 8 bits
loop0:		lda #$30		;static pattern riot
		asl avar 		;test output bit
		bcc dout		;data-out low
		ora #$04		;data-out high
dout:		sta orb			;output to riot
		ora #$08		;set clock
		sta orb			;output to riot
		dex			;loop counter
		bne loop0		;end of loop
		lda #$39		;set load-out
		sta orb			;output to riot
		sty avar		;restore avar
		cli			;enable interrupt
		rts			;return to caller
		;**************************************
		; Routines for interface input control
		; Call in using SYS command
		;**************************************
		; Entry point for both digital and
		; analog input
		;**************************************
_ftbinp:	sei			;disable interrupt
 		cmp #EX			;ex analog input?
 		beq pots		;go to pots
 		cmp #EY			;ey analog input?
		beq pots		;go to pots
 		sta mask		;save input mask
 		;**************************************
 		; Interface Control
 		; for digital input
 		; Uses X- and Y-registers
		; Result in A and X-register
 		;**************************************
		lda #$32		;set load-in
		sta orb			;output to riot
		ora #$08		;set clock
		sta orb			;output to riot
		ldx #$08		;loop counter for 8 bit
loop1:		asl a			;shift left a-reg.
		bit orb			;test data-in
		bpl makein		;data-in is low
		ora #$01		;data-in is high
makein:		ldy #$30		;reset clock
		sty orb			;output to riot
		ldy #$38		;set clock
		sty orb			;output to riot
		dex			;decrement loop counter
		bne loop1		;end of loop
		and mask		;mask bit
 		;tay			;save in y-register
 		beq done		;return 0
 		lda #$01		;return 1
		bne done		;return to caller
; 		;**************************************
; 		; Analog input
; 		; If the argument is either $90 or $A0
; 		; an analog input is invoked. Control
; 		; jumps here.
; 		; Uses A-, X- and Y-registers
		; Result in A- and Y-registers
; 		;**************************************
pots:		ldx #$ff		;set count register to $ffff
		stx t2cl
		stx t2ch
		ldx #%100000		;set t2 to pulse count down
		stx acr
		sta orb			;trigger one-shot
		ldx #$3a		;reset trigger
		stx orb			;output to userport
tst:		lda t2cl		;test timer low register
		ldx #$03		;delay loop
delay:		dex
		bne delay
		sec			;subtract timer low reg.
		sbc t2cl		;from previous value.
		bne tst			;pulses still arriving?
		ldx #$38		;set clock, reset load-in
		stx orb			;output to userport
		sec 			;calculate contents
		lda #$ff
		sbc t2ch 		;high byte
		tax			;in x register
		lda #$ff
		sbc t2cl		;low byte in a reg
done:		cli			;enable interrupts
		rts			;and return to caller