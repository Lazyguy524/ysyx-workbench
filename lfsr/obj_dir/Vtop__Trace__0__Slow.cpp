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
    tracep->declBit(c+4,"button", false,-1);
    tracep->declBus(c+5,"seg0", false,-1, 6,0);
    tracep->declBus(c+6,"seg1", false,-1, 6,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+4,"button", false,-1);
    tracep->declBus(c+5,"seg0", false,-1, 6,0);
    tracep->declBus(c+6,"seg1", false,-1, 6,0);
    tracep->declBit(c+7,"clk", false,-1);
    tracep->declBus(c+1,"lfsr_out", false,-1, 7,0);
    tracep->pushNamePrefix("b7s ");
    tracep->declBus(c+1,"b", false,-1, 7,0);
    tracep->declBus(c+5,"h", false,-1, 6,0);
    tracep->declBus(c+6,"h1", false,-1, 6,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("lfsr0 ");
    tracep->declBit(c+7,"clk", false,-1);
    tracep->declBus(c+1,"lfsr_out", false,-1, 7,0);
    tracep->declBus(c+2,"lfsr_reg", false,-1, 7,0);
    tracep->declBit(c+3,"x8", false,-1);
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
    bufp->fullCData(oldp+1,(vlSelf->top__DOT__lfsr_out),8);
    bufp->fullCData(oldp+2,(vlSelf->top__DOT__lfsr0__DOT__lfsr_reg),8);
    bufp->fullBit(oldp+3,(vlSelf->top__DOT__lfsr0__DOT__x8));
    bufp->fullBit(oldp+4,(vlSelf->button));
    bufp->fullCData(oldp+5,(vlSelf->seg0),7);
    bufp->fullCData(oldp+6,(vlSelf->seg1),7);
    bufp->fullBit(oldp+7,(vlSelf->top__DOT__clk));
}
