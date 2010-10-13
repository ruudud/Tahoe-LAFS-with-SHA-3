
LD       = $(CC)
CC       = gcc
CC_OPTS  = -Wall -O3 -fomit-frame-pointer

VPATH = ..

OBJ = obj

REGRESS = C_OPTIMIZED
CFG_DEF = -DCONFIG_C_OPTIMIZED -DIMPL_NAME='"$(REGRESS)"' -DTEST_DIR='"../"'

PROGRAM = chkKAT speed

C_PROGRAM = chkKAT.o speed.o

C_TARGETS = SHA3api_ref.o fugue.o

F_TARGETS = fugue_256.o fugue_384.o fugue_512.o

.PHONY: default objs warn clean deps regress regress-all

default: warn
	@if [ -d $(OBJ) ] ; then true; else mkdir $(OBJ); fi
	@$(MAKE) -s -f ../Makefile -C $(OBJ) deps
	@$(MAKE) -s -f ../Makefile -C $(OBJ) INCLUDE_DEPS=1 objs

objs: $(PROGRAM)
	@cp -u $(PROGRAM) ..

warn:
	@echo "Making `pwd`"

$(PROGRAM): %: %.o $(C_TARGETS) $(F_TARGETS)
	@echo "=> Linking    $@"
	@$(LD) -lm -o $@ $< $(C_TARGETS) $(F_TARGETS)

$(C_PROGRAM) $(C_TARGETS) $(F_TARGETS): %.o: %.c
	@echo "-> Compiling  $(<F)"
	@$(CC) $(CC_OPTS) $(CFG_DEF) -c $<

$(PROGRAM) $(C_PROGRAM) $(C_TARGETS) $(F_TARGETS): Makefile

clean:
	@echo "Cleaning `pwd`"
	@(rm -rf $(PROGRAM) *.exe *.obj $(OBJ))

deps: ${C_PROGRAM:.o=.d} ${C_TARGETS:.o=.d} ${F_TARGETS:.o=.d}

%.d: %.c
	@$(CC) -M $(CC_OPTS) $(CFG_DEF) $< > $@

ifdef INCLUDE_DEPS
include ${C_PROGRAM:.o=.d} ${C_TARGETS:.o=.d} ${F_TARGETS:.o=.d}
endif

regress: default
	@echo "Starting $(REGRESS) regression tests @ `date`"
	@./chkKAT -s
	@echo "Completed $(REGRESS) regression tests @ `date`"

regress-all: default
	@echo "Starting $(REGRESS) regression tests @ `date`"
	@./chkKAT -a
	@echo "Completed $(REGRESS) regression tests @ `date`"
