;**************************************
; KIM ROM routines
;**************************************
getch		= $1e5a			; get ascii character from tty
outch		= $1ea0			; print ascii character on tty
prtbyt		= $1e3b			; print two hex characters on tty

.export _cgetc, _cputc, _cputs, _cputhex8
.importzp ptr1

.segment "CODE"

; read a character from tty (blocking)
.proc _cgetc
		jsr	getch		; get character from tty
		and     #$7f		; clear top bit
		rts			; and done
.endproc

; output a character to tty
.proc _cputc
		jsr	outch		; output character to tty
		rts
.endproc

.proc _cputs
		sta     ptr1            ; save s
        	stx     ptr1+1
loop:
		ldy     #0
		lda     (ptr1),y
		beq     done
		jsr     _cputc		; output char
		inc     ptr1
		bne     loop
		inc     ptr1+1
		bne     loop
done:		rts
.endproc

; output a char as two hex
.proc _cputhex8
		jsr 	prtbyt		; output char as hex to tty
		rts
.endproc