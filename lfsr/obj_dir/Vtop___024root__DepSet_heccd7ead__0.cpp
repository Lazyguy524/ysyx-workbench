// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__clk = (1U & (~ (IData)(vlSelf->top__DOT__clk)));
}

extern const VlUnpacked<CData/*6:0*/, 256> Vtop__ConstPool__TABLE_h99f1c24f_0;
extern const VlUnpacked<CData/*6:0*/, 256> Vtop__ConstPool__TABLE_hbe312f20_0;

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    // Init
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*0:0*/ __Vdly__top__DOT__lfsr0__DOT__x8;
    __Vdly__top__DOT__lfsr0__DOT__x8 = 0;
    CData/*7:0*/ __Vdly__top__DOT__lfsr0__DOT__lfsr_reg;
    __Vdly__top__DOT__lfsr0__DOT__lfsr_reg = 0;
    // Body
    __Vdly__top__DOT__lfsr0__DOT__lfsr_reg = vlSelf->top__DOT__lfsr0__DOT__lfsr_reg;
    __Vdly__top__DOT__lfsr0__DOT__x8 = vlSelf->top__DOT__lfsr0__DOT__x8;
    __Vdly__top__DOT__lfsr0__DOT__x8 = (1U & VL_REDXOR_8(
                                                         (0x1dU 
                                                          & (IData)(vlSelf->top__DOT__lfsr0__DOT__lfsr_reg))));
    __Vdly__top__DOT__lfsr0__DOT__lfsr_reg = (((IData)(vlSelf->top__DOT__lfsr0__DOT__x8) 
                                               << 7U) 
                                              | (0x7fU 
                                                 & ((IData)(vlSelf->top__DOT__lfsr0__DOT__lfsr_reg) 
                                                    >> 1U)));
    vlSelf->top__DOT__lfsr_out = vlSelf->top__DOT__lfsr0__DOT__lfsr_reg;
    vlSelf->top__DOT__lfsr0__DOT__x8 = __Vdly__top__DOT__lfsr0__DOT__x8;
    vlSelf->top__DOT__lfsr0__DOT__lfsr_reg = __Vdly__top__DOT__lfsr0__DOT__lfsr_reg;
    __Vtableidx1 = vlSelf->top__DOT__lfsr_out;
    vlSelf->seg0 = Vtop__ConstPool__TABLE_h99f1c24f_0
        [__Vtableidx1];
    vlSelf->seg1 = Vtop__ConstPool__TABLE_hbe312f20_0
        [__Vtableidx1];
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    VlTriggerVec<2> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("vsrc/top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("vsrc/top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->button & 0xfeU))) {
        Verilated::overWidthError("button");}
}
#endif  // VL_DEBUG