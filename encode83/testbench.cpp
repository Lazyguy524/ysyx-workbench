#include "Vencode83.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated.h"
#include "verilated_vcd_c.h"


VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vencode83* top;

void step_and_dump_wave(){
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void sim_init(){
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vencode83;
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
  top->en=0b0; top->x =0b00000000; step_and_dump_wave();
               top->x =0b00000001; step_and_dump_wave();
               top->x =0b00000010; step_and_dump_wave();
               top->x =0b00000100; step_and_dump_wave();
               top->x =0b00001000; step_and_dump_wave();
  top->en=0b1; top->x =0b00000000; step_and_dump_wave();
               top->x =0b00000001; step_and_dump_wave();
               top->x =0b00000010; step_and_dump_wave();
               top->x =0b00000100; step_and_dump_wave();
               top->x =0b00001000; step_and_dump_wave();
               top->x =0b00001001; step_and_dump_wave();
               top->x =0b00001010; step_and_dump_wave();
               top->x =0b00001100; step_and_dump_wave();
               top->x =0b00011000; step_and_dump_wave();
  sim_exit();
  return 0;
}
