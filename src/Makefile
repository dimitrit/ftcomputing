DIRS := lib diag 30408

define DIR_make
( cd $(1) && make $@ ) ;
endef

all:
	$(foreach dir,$(DIRS),$(call DIR_make,$(dir)))


clean:
	$(foreach dir,$(DIRS),$(call DIR_make,$(dir)))

.PHONY: all clean
