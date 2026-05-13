; motor.a65 - simple motor control


crlf		= $1e2f
getch		= $1e5a
outsp		= $1e9e
outch		= $1ea0

		.include "ftcomputing.inc"

		.import _ftinit, _ftbinp, _ftboutp

		.segment "ZEROPAGE"
id:		.res 1
mtr:		.res 1
dir:		.res 1

		.segment "CODE"

		cld
		lda #'1'
		sta id
		lda #M1
		sta mtr
		lda #CW
		sta dir
 		jsr _ftinit		; initialise interface
main:		jsr crlf
		lda id
		jsr outch
		lda #'>'
		jsr outch
		jsr outsp
		jsr getch
		cmp #'L'
		bne isright
		lda #CCW
		sta dir
		bne motor
isright:	cmp #'R'
		bne select
		lda #CW
		sta dir
		bne motor
select:		tax
		clc
		sbc #'0'-1
		bmi main
		cmp #5
		bcs main
		tay
		stx id
		lda #M1
		sta mtr
loop:		dey
		beq main
		asl mtr
		asl mtr
		bne loop
motor:		lda mtr			; get motor
		ldx dir			; and direction
		jsr _ftboutp		; and apply
		jsr delay
		lda mtr			; get motor
		ldx #STOP		; set motor off
		jsr _ftboutp
		jmp main

delay:		ldy #$a0
dly0:		ldx #$ff
dly1:		dex
        	bne dly1
		dey
		bne dly0
		rts

		.end