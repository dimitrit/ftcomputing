CC=cc65
CFLAGS=-t kim1
AS=ca65
AFLAGS=-t kim1
LIB_PATH=../lib
MAKEFLAGS += -r

target = rob4.pap

default: all

all: $(target)

%.pap: %.bin
	srec_cat $< -binary -offset 0x200 -output $@ -MOS_Technologies

%.bin: %.o
	ld65 -L$(LIB_PATH) -o $@ -t kim1 $^ ftcomputing.lib conio.lib kim1.lib 

%.s: %.c
	$(CC) $(CFLAGS) -I$(LIB_PATH) $<

%.o: %.s
	$(AS) $(AFLAGS) -l $(basename $<).lst $<

clean:
	@rm -f *.lst *.img *.com *.bin *.obj *.hex *.pap *.o

.PHONY: clean 
.PRECIOUS: %.pap
