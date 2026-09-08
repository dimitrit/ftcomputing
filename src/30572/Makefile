AS=ca65
CC=cl65
CFLAGS=-c -t kim1
LIB_PATH=../lib

target = training.pap

default: all

all: $(target)

%.pap: %.bin
	srec_cat $< -binary -offset 0x2000 -output $@ -MOS_Technologies

%.bin: %.o ft30572.o
	ld65 -L$(LIB_PATH) -o $@ -C kim1-60k.cfg $^ ftcomputing.lib conio.lib kim1.lib

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIB_PATH) -L$(LIB_PATH) $<

%.o: %.s
	$(AS) -l $(basename $<).lst $<

clean:
	@rm -f *.lst *.img *.com *.bin *.obj *.hex *.pap *.o

.PHONY: clean
.PRECIOUS: %.pap %.bin
