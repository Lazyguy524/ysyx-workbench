#include "Vtop.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated.h"
#include "verilated_fst_c.h"
#include <verilated.h>
#include <nvboard.h>


static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* top);

int main(int argc, char** argv) {
  nvboard_bind_all_pins(&dut);
  nvboard_init();
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);
  Vtop* top = new Vtop{contextp};
      
  // Verilated::traceEverOn(true);
  // VerilatedFstC* tfp = new VerilatedFstC;
  // top->trace(tfp,0);
  // tfp->open("waveform.fst");

  int loopCount = 100;
  while (1) {
    nvboard_update();
    dut.eval();
  }

  // tfp->close();
  delete top;
  delete contextp;
  
  return 0;
}
