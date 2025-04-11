// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+34,"clk", false,-1);
    tracep->declBit(c+35,"rst", false,-1);
    tracep->declBus(c+36,"inst", false,-1, 31,0);
    tracep->declBus(c+37,"pc", false,-1, 31,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+34,"clk", false,-1);
    tracep->declBit(c+35,"rst", false,-1);
    tracep->declBus(c+36,"inst", false,-1, 31,0);
    tracep->declBus(c+37,"pc", false,-1, 31,0);
    tracep->declBus(c+38,"rs1_addr", false,-1, 4,0);
    tracep->declBus(c+39,"rd_addr", false,-1, 4,0);
    tracep->declBus(c+40,"imm", false,-1, 31,0);
    tracep->declBus(c+41,"alu_op", false,-1, 2,0);
    tracep->declBus(c+42,"rs1_data", false,-1, 31,0);
    tracep->declBus(c+43,"rd_data", false,-1, 31,0);
    tracep->declBit(c+44,"reg_write_en", false,-1);
    tracep->pushNamePrefix("u_exu ");
    tracep->declBus(c+40,"imm", false,-1, 31,0);
    tracep->declBus(c+41,"alu_op", false,-1, 2,0);
    tracep->declBus(c+42,"rs1_data", false,-1, 31,0);
    tracep->declBus(c+43,"rd_data", false,-1, 31,0);
    tracep->declBus(c+43,"result", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_idu ");
    tracep->declBus(c+36,"inst", false,-1, 31,0);
    tracep->declBus(c+40,"imm", false,-1, 31,0);
    tracep->declBus(c+38,"rs1_addr", false,-1, 4,0);
    tracep->declBus(c+39,"rd_addr", false,-1, 4,0);
    tracep->declBus(c+41,"alu_op", false,-1, 2,0);
    tracep->declBit(c+44,"reg_write_en", false,-1);
    tracep->declBus(c+45,"opcode", false,-1, 6,0);
    tracep->declBus(c+45,"op", false,-1, 6,0);
    tracep->declBus(c+41,"func3", false,-1, 2,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_ifu ");
    tracep->declBit(c+34,"clk", false,-1);
    tracep->declBit(c+35,"rst", false,-1);
    tracep->declBus(c+37,"pc", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_reg ");
    tracep->declBit(c+34,"clk", false,-1);
    tracep->declBit(c+35,"rst", false,-1);
    tracep->declBus(c+38,"rs1", false,-1, 4,0);
    tracep->declBus(c+39,"rd", false,-1, 4,0);
    tracep->declBus(c+43,"rd_data", false,-1, 31,0);
    tracep->declBit(c+44,"write_en", false,-1);
    tracep->declBus(c+42,"rs1_data", false,-1, 31,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+1+i*1,"reg_file", true,(i+0), 31,0);
    }
    tracep->declBus(c+33,"i", false,-1, 31,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelf->top__DOT__u_reg__DOT__reg_file[0]),32);
    bufp->fullIData(oldp+2,(vlSelf->top__DOT__u_reg__DOT__reg_file[1]),32);
    bufp->fullIData(oldp+3,(vlSelf->top__DOT__u_reg__DOT__reg_file[2]),32);
    bufp->fullIData(oldp+4,(vlSelf->top__DOT__u_reg__DOT__reg_file[3]),32);
    bufp->fullIData(oldp+5,(vlSelf->top__DOT__u_reg__DOT__reg_file[4]),32);
    bufp->fullIData(oldp+6,(vlSelf->top__DOT__u_reg__DOT__reg_file[5]),32);
    bufp->fullIData(oldp+7,(vlSelf->top__DOT__u_reg__DOT__reg_file[6]),32);
    bufp->fullIData(oldp+8,(vlSelf->top__DOT__u_reg__DOT__reg_file[7]),32);
    bufp->fullIData(oldp+9,(vlSelf->top__DOT__u_reg__DOT__reg_file[8]),32);
    bufp->fullIData(oldp+10,(vlSelf->top__DOT__u_reg__DOT__reg_file[9]),32);
    bufp->fullIData(oldp+11,(vlSelf->top__DOT__u_reg__DOT__reg_file[10]),32);
    bufp->fullIData(oldp+12,(vlSelf->top__DOT__u_reg__DOT__reg_file[11]),32);
    bufp->fullIData(oldp+13,(vlSelf->top__DOT__u_reg__DOT__reg_file[12]),32);
    bufp->fullIData(oldp+14,(vlSelf->top__DOT__u_reg__DOT__reg_file[13]),32);
    bufp->fullIData(oldp+15,(vlSelf->top__DOT__u_reg__DOT__reg_file[14]),32);
    bufp->fullIData(oldp+16,(vlSelf->top__DOT__u_reg__DOT__reg_file[15]),32);
    bufp->fullIData(oldp+17,(vlSelf->top__DOT__u_reg__DOT__reg_file[16]),32);
    bufp->fullIData(oldp+18,(vlSelf->top__DOT__u_reg__DOT__reg_file[17]),32);
    bufp->fullIData(oldp+19,(vlSelf->top__DOT__u_reg__DOT__reg_file[18]),32);
    bufp->fullIData(oldp+20,(vlSelf->top__DOT__u_reg__DOT__reg_file[19]),32);
    bufp->fullIData(oldp+21,(vlSelf->top__DOT__u_reg__DOT__reg_file[20]),32);
    bufp->fullIData(oldp+22,(vlSelf->top__DOT__u_reg__DOT__reg_file[21]),32);
    bufp->fullIData(oldp+23,(vlSelf->top__DOT__u_reg__DOT__reg_file[22]),32);
    bufp->fullIData(oldp+24,(vlSelf->top__DOT__u_reg__DOT__reg_file[23]),32);
    bufp->fullIData(oldp+25,(vlSelf->top__DOT__u_reg__DOT__reg_file[24]),32);
    bufp->fullIData(oldp+26,(vlSelf->top__DOT__u_reg__DOT__reg_file[25]),32);
    bufp->fullIData(oldp+27,(vlSelf->top__DOT__u_reg__DOT__reg_file[26]),32);
    bufp->fullIData(oldp+28,(vlSelf->top__DOT__u_reg__DOT__reg_file[27]),32);
    bufp->fullIData(oldp+29,(vlSelf->top__DOT__u_reg__DOT__reg_file[28]),32);
    bufp->fullIData(oldp+30,(vlSelf->top__DOT__u_reg__DOT__reg_file[29]),32);
    bufp->fullIData(oldp+31,(vlSelf->top__DOT__u_reg__DOT__reg_file[30]),32);
    bufp->fullIData(oldp+32,(vlSelf->top__DOT__u_reg__DOT__reg_file[31]),32);
    bufp->fullIData(oldp+33,(vlSelf->top__DOT__u_reg__DOT__i),32);
    bufp->fullBit(oldp+34,(vlSelf->clk));
    bufp->fullBit(oldp+35,(vlSelf->rst));
    bufp->fullIData(oldp+36,(vlSelf->inst),32);
    bufp->fullIData(oldp+37,(vlSelf->pc),32);
    bufp->fullCData(oldp+38,((0x1fU & (vlSelf->inst 
                                       >> 0xfU))),5);
    bufp->fullCData(oldp+39,((0x1fU & (vlSelf->inst 
                                       >> 7U))),5);
    bufp->fullIData(oldp+40,(vlSelf->top__DOT__imm),32);
    bufp->fullCData(oldp+41,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->fullIData(oldp+42,(vlSelf->top__DOT__rs1_data),32);
    bufp->fullIData(oldp+43,(((0x4000U & vlSelf->inst)
                               ? ((0x2000U & vlSelf->inst)
                                   ? ((0x1000U & vlSelf->inst)
                                       ? (vlSelf->top__DOT__rs1_data 
                                          & vlSelf->top__DOT__imm)
                                       : (vlSelf->top__DOT__rs1_data 
                                          | vlSelf->top__DOT__imm))
                                   : ((0x1000U & vlSelf->inst)
                                       ? 0U : (vlSelf->top__DOT__rs1_data 
                                               ^ vlSelf->top__DOT__imm)))
                               : ((0x2000U & vlSelf->inst)
                                   ? 0U : ((0x1000U 
                                            & vlSelf->inst)
                                            ? 0U : 
                                           (vlSelf->top__DOT__rs1_data 
                                            + vlSelf->top__DOT__imm))))),32);
    bufp->fullBit(oldp+44,((0x13U == (0x7fU & vlSelf->inst))));
    bufp->fullCData(oldp+45,((0x7fU & vlSelf->inst)),7);
}
