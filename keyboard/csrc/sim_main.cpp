#include "Vtop.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated.h"
#include "verilated_fst_c.h"
#include <verilated.h>
#include <nvboard.h>


static TOP_NAME top;

void nvboard_bind_all_pins(TOP_NAME* top);

void single_cycle() {
  top.clk = 0; top.eval();
  top.clk = 1; top.eval();
}

void reset(int n) {
  top.rst = 1;
  while (n -- > 0)
  {
    single_cycle();
  }
  top.rst = 0;
}

int main(int argc, char** argv) {
  nvboard_bind_all_pins(&top);
  nvboard_init();
  // VerilatedContext* contextp = new VerilatedContext;
  // contextp->commandArgs(argc, argv);
  // top = new Vtop{contextp};

  reset(10);

  while (1) {
    nvboard_update();
    single_cycle();
    top.eval();
  }

  // tfp->close();
  // delete top;
  // delete contextp;
  
  return 0;
}
