cmd_/home/ysyx/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/utils/disasm.o := unused

source_/home/ysyx/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/utils/disasm.o := src/utils/disasm.c

deps_/home/ysyx/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/utils/disasm.o := \
    $(wildcard include/config/isa/x86.h) \
    $(wildcard include/config/isa/mips32.h) \
    $(wildcard include/config/isa/riscv.h) \
    $(wildcard include/config/isa/loongarch32r.h) \
    $(wildcard include/config/isa64.h) \
  tools/capstone/repo/include/capstone/capstone.h \
  tools/capstone/repo/include/capstone/cs_operand.h \
  tools/capstone/repo/include/capstone/platform.h \
  tools/capstone/repo/include/capstone/arm.h \
  tools/capstone/repo/include/capstone/aarch64.h \
  tools/capstone/repo/include/capstone/m68k.h \
  tools/capstone/repo/include/capstone/mips.h \
  tools/capstone/repo/include/capstone/ppc.h \
  tools/capstone/repo/include/capstone/sparc.h \
  tools/capstone/repo/include/capstone/systemz.h \
  tools/capstone/repo/include/capstone/x86.h \
  tools/capstone/repo/include/capstone/xcore.h \
  tools/capstone/repo/include/capstone/tms320c64x.h \
  tools/capstone/repo/include/capstone/m680x.h \
  tools/capstone/repo/include/capstone/evm.h \
  tools/capstone/repo/include/capstone/riscv.h \
  tools/capstone/repo/include/capstone/wasm.h \
  tools/capstone/repo/include/capstone/mos65xx.h \
  tools/capstone/repo/include/capstone/bpf.h \
  tools/capstone/repo/include/capstone/sh.h \
  tools/capstone/repo/include/capstone/tricore.h \
  tools/capstone/repo/include/capstone/alpha.h \
  tools/capstone/repo/include/capstone/hppa.h \
  tools/capstone/repo/include/capstone/loongarch.h \
  tools/capstone/repo/include/capstone/xtensa.h \
  /home/ysyx/ysyx-workbench/nemu/include/common.h \
    $(wildcard include/config/target/am.h) \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
  /home/ysyx/ysyx-workbench/nemu/include/macro.h \
  /home/ysyx/ysyx-workbench/nemu/include/debug.h \
  /home/ysyx/ysyx-workbench/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \

/home/ysyx/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/utils/disasm.o: $(deps_/home/ysyx/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/utils/disasm.o)

$(deps_/home/ysyx/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/utils/disasm.o):
