  #include "Vtop.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <assert.h>
  #include "verilated.h"
  #include "verilated_fst_c.h"
  int main(int argc, char** argv) {
      VerilatedContext* contextp = new VerilatedContext;
      contextp->commandArgs(argc, argv);
      Vtop* top = new Vtop{contextp};
      
      Verilated::traceEverOn(true);
      VerilatedFstC* tfp = new VerilatedFstC;
      top->trace(tfp,0);
      tfp->open("waveform.fst");

      int loopCount = 100;
      while (loopCount >0) {
	      int a = rand() & 1;
	      int b = rand() & 1;
	      top->a = a;
	      top->b = b;
	      top->eval();
	      tfp->dump(contextp->time());
        contextp->timeInc(1);//仿真时间推进1个时间单位
	      printf("a = %d, b = %d, f = %d\n", a, b, top->f);
	      assert(top->f == (a ^ b));
	      loopCount--;
      }

      tfp->close();
      delete top;
      delete contextp;
      return 0;
  }
