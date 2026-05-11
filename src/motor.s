; motor.a65 - simple motor control


CRLF		= $1E2F
GETCH		= $1E5A
OUTSP		= $1E9E
OUTCH		= $1EA0

		.INCLUDE "FTCOMPUTING.INC"

		.IMPORT FTINIT, FTBINP, FTBOUTP

		.SEGMENT "ZEROPAGE"
ID:		.RES 1
MTR:		.RES 1
DIR:		.RES 1

		.SEGMENT "CODE"

		CLD
		LDA #'1'
		STA ID
		LDA #M1
		STA MTR
		LDA #CW
		STA DIR
 		JSR FTINIT		; Initialise interface
MAIN:		JSR CRLF
		LDA ID
		JSR OUTCH
		LDA #'>'
		JSR OUTCH
		JSR OUTSP
		JSR GETCH
		CMP #'L'
		BNE ISRIGHT
		LDA #CCW
		STA DIR
		BNE MOTOR
ISRIGHT:	CMP #'R'
		BNE SELECT
		LDA #CW
		STA DIR
		BNE MOTOR
SELECT:		TAX
		CLC
		SBC #'0'-1
		BMI MAIN
		CMP #5
		BCS MAIN
		TAY
		STX ID
		LDA #M1
		STA MTR
LOOP:		DEY
		BEQ MAIN
		ASL MTR
		ASL MTR
		BNE LOOP
MOTOR:		LDA MTR			; Get motor
		LDX DIR			; And direction
		JSR FTBOUTP		; And apply
		JSR DELAY
		LDA MTR			; Get motor
		LDX #STOP		; Set motor off
		JSR FTBOUTP
		JMP MAIN

DELAY:		LDY #$A0
DLY0:		LDX #$FF
DLY1:		DEX
        	BNE DLY1
		DEY
		BNE DLY0
		RTS

		.END