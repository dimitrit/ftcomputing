target = irobots.pap

default: all

all: $(target)

%.pap: %.bin
	srec_cat $< -binary -offset 0x200 -output $@ -MOS_Technologies

%.bin: %.o viaifdrv.o conio.o
	ld65 -o $@ -t kim1 $^ kim1.lib

%.s: %.c
	cc65 -t kim1 $<

%.o: %.s
	ca65 -t kim1 -l $(basename $<).lst $<

clean:
	@rm -f *.lst *.img *.com *.bin *.obj *.hex *.pap *.o

.PHONY: clean debug test
.PRECIOUS: %.hex %.bin %.pap
