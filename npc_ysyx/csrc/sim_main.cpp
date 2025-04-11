#include <Vtop.h>
#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include <verilated.h>
#include <verilated_fst_c.h>
#include <svdpi.h>

static const uint32_t inst[] = {
  0b00000000010100000000000010010011, // addi x1, x0, 5
  0b00000000000100000000000100010011, // addi x2, x0, 1
  0b00000000001000000000000110010011, // addi x3, x0, 2
  0b00000000000100000000000001110011, // ebreak
  0b00000000010100001000000100010011, // addi x2, x1, 5
};

uint32_t *init_mem(size_t size) {
  uint32_t* mem = (uint32_t*)malloc(size * sizeof(uint32_t));
  if (mem == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(mem, inst, sizeof(inst));
  return mem;
}

uint32_t guest_to_host(uint32_t addr) {
  return addr - 0x80000000; // 假设物理内存从0开始
}

uint32_t pmem_read(uint32_t *mem, uint32_t vaddr) {
  uint32_t paddr = guest_to_host(vaddr);
  if (paddr >= sizeof(inst)) { // 检查内存访问边界
    printf("Memory access out of bounds: 0x%08x\n", vaddr);
    return 0;
  }
  return mem[paddr >> 2]; // 使用右移2位代替除以4
}

// 声明为指针
static Vtop* top;

void single_cycle() {
  top->clk = 0;
  top->eval();
  top->clk = 1;
  top->eval();
}

static void reset(int n) {
  top->rst = 1;
  while (n-- > 0) single_cycle(); // 生成时钟边沿
  top->rst = 0;
}

extern "C" void npc_trap(){
  printf("npc_trap\n");
  Verilated::gotFinish(true);
  // exit(0);
}

int main() {
  // 首先启用波形跟踪 - 在任何其他初始化之前
  Verilated::traceEverOn(true);
  
  // 设置上下文
  VerilatedContext* contextp = new VerilatedContext;
  contextp->traceEverOn(true);  // 也在上下文中启用
  
  // 创建模块实例
  top = new Vtop(contextp);
  
  // 初始化内存
  uint32_t *mem = init_mem(sizeof(inst) / sizeof(uint32_t));
  
  // 设置波形追踪 - 在任何调用eval()之前
  VerilatedFstC* tfp = new VerilatedFstC;
  top->trace(tfp, 5);
  tfp->open("waveform.fst");
  
  // 在对时间进行任何操作前将时间设为0
  contextp->timeInc(0);
  
  // 复位处理器
  reset(10);
  
  // for(int i=0; i<5; i++){
  //   if(Verilated::gotFinish()) {
  //     printf("Simulation finished\n");
  //     break;
  //   }
  //   top->inst = pmem_read(mem, top->pc);
  //   printf("Cycle %d: PC = 0x%08x, Inst = 0x%08x\n", i, top->pc, top->inst);
  //   single_cycle();
  //   tfp->dump(contextp->time());
  //   contextp->timeInc(1);
  // }
  
  while (!Verilated::gotFinish()) {
    top->inst = pmem_read(mem, top->pc);
    printf("PC = 0x%08x, Inst = 0x%08x\n", top->pc, top->inst);
    single_cycle();
    tfp->dump(contextp->time());
    contextp->timeInc(1);
  }
  
  // 清理资源
  tfp->close();
  delete top;
  delete tfp;
  delete contextp;
  free(mem);
  
  return 0;
}