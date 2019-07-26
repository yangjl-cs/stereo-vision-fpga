#include "xil_printf.h"
#include "xdebug.h"
#include "xstatus.h"

#include "dynclk_ctrl.h"
#include "dynclk/dynclk.h"

DynclkCtrl::DynclkCtrl() {
    this->state = DYNCLK_STOPPED;
}

DynclkCtrl::~DynclkCtrl() {
    this->stop();
}

int DynclkCtrl::init(u32 base_addr, const double freq) {
    ClkConfig clk_reg;
    ClkMode clk_mode;

    this->base_addr = base_addr;

    ClkFindParams(freq, &clk_mode);
    this->pxl_freq = clk_mode.freq;
    if (!ClkFindReg(&clk_reg, &clk_mode))
    {
        xdbg_printf(XDBG_DEBUG_GENERAL, "*E* Failed in calculating DynClk register values\n");
        return XST_FAILURE;
    }
    ClkWriteReg(&clk_reg, this->base_addr);
    ClkStart(this->base_addr);

    return XST_SUCCESS;
}

int DynclkCtrl::start(const double freq) {
    ClkConfig clk_reg;
    ClkMode clk_mode;

    if (this->state == DYNCLK_RUNNING)
    {
        return XST_SUCCESS;
    }
    ClkFindParams(freq, &clk_mode);

    this->pxl_freq = clk_mode.freq;

    if (!ClkFindReg(&clk_reg, &clk_mode)) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "*E* Failed in calculating CLK register values\n");
        return XST_FAILURE;
    }
    ClkWriteReg(&clk_reg, this->base_addr);
    ClkStop(this->base_addr);
    ClkStart(this->base_addr);

    this->state = DYNCLK_RUNNING;

    return XST_SUCCESS;
}

int DynclkCtrl::stop() {
    if (this->state == DYNCLK_STOPPED)
    {
        return XST_SUCCESS;
    }

    ClkStop(this->base_addr);
    this->state = DYNCLK_STOPPED;

    return XST_SUCCESS;
}
