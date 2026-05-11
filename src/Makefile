target = motor.pap

default: all

all: $(target)

%.pap: %.bin
	srec_cat $< -Binary -offset 512 -output $@ -MOS_Technologies

motor.bin: motor.o viaifdrv.o
	ld65 -o $@ -t kim1 $? kim1.lib

%.o: %.s
	ca65 -t kim1 $<

clean:
	@rm -f *.lst *.img *.com *.bin *.obj *.hex *.pap *.o

.PHONY: clean debug test
.PRECIOUS: %.hex %.bin %.pap
