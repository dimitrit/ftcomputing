		.export _moveto

		.import _ftboutp, _ftbinp
		.import popa, pusha

		.importzp ptr1, ptr2, ptr3
		.importzp tmp2, tmp3

steps	= ptr1		; number of steps to run
actual	= ptr3		; actual number of steps
dir	= ptr2		; motor direction
ctr	= ptr2+1	; step sensor
mtr	= tmp2		; motor

STOP	= %11111111

.proc _moveto
		sei 			; disable interrupt
                sta     steps		; save number of steps
                stx     steps+1
		jsr	popa		; get direction
		sta	dir
		jsr	popa		; get step counter
		sta	ctr
		jsr	popa		; get motor
		sta	mtr
		lda	#0		; clear actual step count
		sta	actual
		sta	actual+1
		lda	ctr		; get sensor
		beq	start		; no sensor, so start motor
		jsr	_ftbinp		; get current sensor value
		sta	tmp3		; and save
start:		lda	mtr		; set motor going in direction
		jsr	pusha
		lda	dir
		jsr	_ftboutp

loop1:		lda	steps		; check if we've done all steps
		ora	steps+1
		beq	done		; yes, all done
loop2:		lda	ctr		; get current step sensor value
		beq	loop3		; no sensor, so skip check
		jsr	_ftbinp
		cmp	tmp3		; and compare with previous
		beq	loop2		; they're still the same, so try again
		sta	tmp3		; save new value
loop3:		inc	actual		; increment actual steps
		bne	count
		inc	actual+1
count:		lda	steps		; decrement steps to do
		bne	decr
		dec	steps+1
decr:		dec	steps
		jmp	loop1
done:		lda	mtr		; stop motor
		jsr	pusha
		lda	#STOP
		jsr	_ftboutp

		lda	actual		; return actual steps counted
		ldx	actual+1
		cli			; re-enable interrupts
		rts
.endproc