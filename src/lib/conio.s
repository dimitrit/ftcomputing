

.export _cgetc, _cgets, _cputc, _cputs, _cputhex8
.export _kbhit, _gotoxy, _revers, _clrscr
.import popa, popax, pusha
.importzp ptr1, tmp1, tmp2

;**************************************
; KIM ROM routines
;**************************************
getch		= $1e5a			; get ascii character from tty
outch		= $1ea0			; print ascii character on tty
prtbyt		= $1e3b			; print two hex characters on tty

;**************************************
; KIM hardware registers
;**************************************
sad		= $1740			; 6530 A data
sbd		= $1742			; 6530 B data

;**************************************
; Misc
;**************************************
esc		= $1b

.segment "CODE"

; Return the character code if a character is waiting on the tty,
; return false if not.
.proc _kbhit
		lda	sad		; check for data on tty
		bmi	nokey
		lda	sbd
		and	#$fe		; set PB0 to U26 low to suppress echo
		sta	sbd
		jsr	getch
		pha
		lda	sbd
		ora	#1		; raise PB0 to U26 to enable echo
		sta	sbd
		pla
		rts
nokey:		lda	#0		; return NULL
		rts
.endproc

; Return a character from the tty. If there is no character available,
; the function waits until the user does press a key.
.proc _cgetc
		jsr	getch		; get character from tty
		and     #$7f		; clear top bit
		rts			; and done
.endproc

; Get a string of characters directly from the console. The function
; returns when size - 1 characters or either CR/LF are read.
; char* __fastcall__ cgets (char* buffer, int size);
.proc _cgets
		sta	tmp1		; store max size of input
                jsr     popax           ; get pointer to result string
                sta     ptr1            ; and save
                stx     ptr1+1
		lda	#0		; clear buffer index pointer
		sta	tmp2
loop:		jsr	getch		; get character
		ldy	tmp2		; get buffer index pointer
		cmp	#$0a		; is it a newline
		beq	done		; yes, done
		cmp	#$0d		; is it a carriage return
		beq	done		; yes, done
		sta	(ptr1),y	; and save character
		inc	tmp2		; increase index pointer
		lda	tmp1		; get max length
		cmp	tmp2		; and compare with current index
		bne	loop		; not yet at max length
done:		lda	#0		; terminate string with NUL
		sta	(ptr1),y
                lda     ptr1            ; point to start of buffer
                ldx     ptr1+1
		rts			; all done!
.endproc

; Output one character at the current cursor position
.proc _cputc
		jmp	outch		; output character to tty
.endproc

; Output a NULL-terminated string at the current cursor position
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
		jmp 	prtbyt
.endproc

; Enable/disable reverse character display. This may not be supported by
; the output device.
.proc _revers
		ldy	#'0'		; default to reverse off
		sty	reverse+2
		cmp	#0
		beq	output
		lda	#'7'		; reverse on
		sta	reverse+2
output:		lda	#<reverse
		ldx	#>reverse
		jsr	_cputs
		rts
reverse:	.byte	esc,"[7m",0
.endproc

; Set the cursor to the specified position
.proc _gotoxy
		pha
		lda	#esc
		jsr	outch
		lda	#'['
		jsr	outch
		pla
		jsr	tobcd
		jsr	prtbyt
		lda	#';'
		jsr	outch
		jsr	popa
		jsr	tobcd
		jsr	prtbyt
		lda	#'H'
		jmp	outch
.endproc

; Clear the whole screen and put the cursor into the top left corner
.proc _clrscr
		lda	#<clearscreen
		ldx	#>clearscreen
		jsr	_cputs
		lda	#0
		jsr	pusha
		lda	#0
		beq	_gotoxy
clearscreen:	.byte 	esc,"[2J",0
.endproc

; Converts a hex value 0-0x63 to BCD 0-99
.proc tobcd
		sta	ptr1
		lda	#0
loop:
		ldx	#$F8         ; SED instruction (opcode $F8)
		asl	ptr1
		sta	ptr1+1
		adc	ptr1+1
		inx
		bne	loop+1
		cld
		rts
.endproc