# Date: 2021/04/25
ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
endif

VPATH = vsrc:csrc

TOP_MODULE = top
TOP_SRC = vsrc/$(TOP_MODULE).v
SIM_SRC = csrc/sim_main.cpp
VFLAGS = --cc --trace-fst --exe --build -j 0 -Wall

all:
	@echo "Write this Makefile by your self."

sim: $(TOP_SRC) $(SIM_SRC)
	$(VERILATOR) $(VFLAGS) $(SIM_SRC)	$(TOP_SRC) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."

include ../Makefile

clean:
	rm -f obj_dir/* *.fst

.PHONY: all sim clean