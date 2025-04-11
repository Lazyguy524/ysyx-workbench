// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgIData(oldp+0,(vlSelf->top__DOT__u_reg__DOT__reg_file[0]),32);
        bufp->chgIData(oldp+1,(vlSelf->top__DOT__u_reg__DOT__reg_file[1]),32);
        bufp->chgIData(oldp+2,(vlSelf->top__DOT__u_reg__DOT__reg_file[2]),32);
        bufp->chgIData(oldp+3,(vlSelf->top__DOT__u_reg__DOT__reg_file[3]),32);
        bufp->chgIData(oldp+4,(vlSelf->top__DOT__u_reg__DOT__reg_file[4]),32);
        bufp->chgIData(oldp+5,(vlSelf->top__DOT__u_reg__DOT__reg_file[5]),32);
        bufp->chgIData(oldp+6,(vlSelf->top__DOT__u_reg__DOT__reg_file[6]),32);
        bufp->chgIData(oldp+7,(vlSelf->top__DOT__u_reg__DOT__reg_file[7]),32);
        bufp->chgIData(oldp+8,(vlSelf->top__DOT__u_reg__DOT__reg_file[8]),32);
        bufp->chgIData(oldp+9,(vlSelf->top__DOT__u_reg__DOT__reg_file[9]),32);
        bufp->chgIData(oldp+10,(vlSelf->top__DOT__u_reg__DOT__reg_file[10]),32);
        bufp->chgIData(oldp+11,(vlSelf->top__DOT__u_reg__DOT__reg_file[11]),32);
        bufp->chgIData(oldp+12,(vlSelf->top__DOT__u_reg__DOT__reg_file[12]),32);
        bufp->chgIData(oldp+13,(vlSelf->top__DOT__u_reg__DOT__reg_file[13]),32);
        bufp->chgIData(oldp+14,(vlSelf->top__DOT__u_reg__DOT__reg_file[14]),32);
        bufp->chgIData(oldp+15,(vlSelf->top__DOT__u_reg__DOT__reg_file[15]),32);
        bufp->chgIData(oldp+16,(vlSelf->top__DOT__u_reg__DOT__reg_file[16]),32);
        bufp->chgIData(oldp+17,(vlSelf->top__DOT__u_reg__DOT__reg_file[17]),32);
        bufp->chgIData(oldp+18,(vlSelf->top__DOT__u_reg__DOT__reg_file[18]),32);
        bufp->chgIData(oldp+19,(vlSelf->top__DOT__u_reg__DOT__reg_file[19]),32);
        bufp->chgIData(oldp+20,(vlSelf->top__DOT__u_reg__DOT__reg_file[20]),32);
        bufp->chgIData(oldp+21,(vlSelf->top__DOT__u_reg__DOT__reg_file[21]),32);
        bufp->chgIData(oldp+22,(vlSelf->top__DOT__u_reg__DOT__reg_file[22]),32);
        bufp->chgIData(oldp+23,(vlSelf->top__DOT__u_reg__DOT__reg_file[23]),32);
        bufp->chgIData(oldp+24,(vlSelf->top__DOT__u_reg__DOT__reg_file[24]),32);
        bufp->chgIData(oldp+25,(vlSelf->top__DOT__u_reg__DOT__reg_file[25]),32);
        bufp->chgIData(oldp+26,(vlSelf->top__DOT__u_reg__DOT__reg_file[26]),32);
        bufp->chgIData(oldp+27,(vlSelf->top__DOT__u_reg__DOT__reg_file[27]),32);
        bufp->chgIData(oldp+28,(vlSelf->top__DOT__u_reg__DOT__reg_file[28]),32);
        bufp->chgIData(oldp+29,(vlSelf->top__DOT__u_reg__DOT__reg_file[29]),32);
        bufp->chgIData(oldp+30,(vlSelf->top__DOT__u_reg__DOT__reg_file[30]),32);
        bufp->chgIData(oldp+31,(vlSelf->top__DOT__u_reg__DOT__reg_file[31]),32);
        bufp->chgIData(oldp+32,(vlSelf->top__DOT__u_reg__DOT__i),32);
    }
    bufp->chgBit(oldp+33,(vlSelf->clk));
    bufp->chgBit(oldp+34,(vlSelf->rst));
    bufp->chgIData(oldp+35,(vlSelf->inst),32);
    bufp->chgIData(oldp+36,(vlSelf->pc),32);
    bufp->chgCData(oldp+37,((0x1fU & (vlSelf->inst 
                                      >> 0xfU))),5);
    bufp->chgCData(oldp+38,((0x1fU & (vlSelf->inst 
                                      >> 7U))),5);
    bufp->chgIData(oldp+39,(vlSelf->top__DOT__imm),32);
    bufp->chgCData(oldp+40,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->chgIData(oldp+41,(vlSelf->top__DOT__rs1_data),32);
    bufp->chgIData(oldp+42,(((0x4000U & vlSelf->inst)
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
                                           ? 0U : (vlSelf->top__DOT__rs1_data 
                                                   + vlSelf->top__DOT__imm))))),32);
    bufp->chgBit(oldp+43,((0x13U == (0x7fU & vlSelf->inst))));
    bufp->chgCData(oldp+44,((0x7fU & vlSelf->inst)),7);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
