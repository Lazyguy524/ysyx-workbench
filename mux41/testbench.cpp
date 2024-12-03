#include "Vmux41b.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated.h"
#include "verilated_vcd_c.h"


VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vmux41b* top;

void step_and_dump_wave(){
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void sim_init(){
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vmux41b;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("dump.vcd");
}

void sim_exit(){
    step_and_dump_wave();
    tfp->close();
}


int main(int argc, char** argv) {
  sim_init();
  top->s=0b00; top->a=0b11100100; step_and_dump_wave();
               top->a=0b11100001; step_and_dump_wave();
  top->s=0b01; top->a=0b11100001; step_and_dump_wave();
               top->a=0b11100100; step_and_dump_wave();
  top->s=0b10; top->a=0b11100001; step_and_dump_wave();
               top->a=0b11011000; step_and_dump_wave();
  top->s=0b11; top->a=0b01111000; step_and_dump_wave();
               top->a=0b10001101; step_and_dump_wave();
  sim_exit();
  return 0;
}
