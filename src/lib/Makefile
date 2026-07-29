AS=ca65
AR=ar65

target = ftcomputing.lib conio.lib

default: all

all: $(target)

ftcomputing.lib: viaifdrv.o 
	$(AR) a $@ $<

conio.lib: conio.o	

viaifdrv.o: viaifdrv.s ftcomputing.h
conio.o: conio.s

%.lib: %.o
	$(AR) a $@ $<

%.o: %.s
	$(AS) -l $(basename $<).lst $<
clean:
	@rm -f *.lst *.lib *.o

.PHONY: clean
.PRECIOUS: %.lib
