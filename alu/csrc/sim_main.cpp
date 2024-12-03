#include "Vtop.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated.h"
#include "verilated_fst_c.h"
#include <verilated.h>
#include <nvboard.h>


static TOP_NAME top;

void nvboard_bind_all_pins(Vtop* top);


int main(int argc, char** argv) {
  nvboard_bind_all_pins(&top);
  nvboard_init();
  // VerilatedContext* contextp = new VerilatedContext;
  // contextp->commandArgs(argc, argv);
  // top = new Vtop{contextp};


  while (1) {
    nvboard_update();
    top.eval();
  }

  // tfp->close();
  // delete top;
  // delete contextp;
  
  return 0;
}
