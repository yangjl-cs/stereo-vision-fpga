#include "xil_printf.h"
#include "xstatus.h"
#include "xdebug.h"

#include "led.h"

Led::Led() {
    p_gpio = &gpio;
}

Led::~Led(){
}

int Led::init(u16 device_id){
    XGpio_Config *config;
    int status;
    config = XGpio_LookupConfig(device_id);
    if (NULL == config) {
        xil_printf("*E* Cannot find LED GPIO configuration\n");
        return XST_FAILURE;
    }
    status = XGpio_CfgInitialize(p_gpio, config, config->BaseAddress);
    if (status != XST_SUCCESS) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "*E* LED GPIO configuration initialization failed\n");
        return XST_FAILURE;
    }
    XGpio_SetDataDirection(p_gpio, 1, 0x0);
    XGpio_SetDataDirection(p_gpio, 2, 0x0);
    XGpio_DiscreteWrite(p_gpio, 1, 0b1111);
    // The RGB LEDs are highly intensive, and should be driven by PWM, which is
    // not implemented yet. So they are disabled by default.
    XGpio_DiscreteWrite(p_gpio, 2, 0b000000);
    return XST_SUCCESS;
}

int Led::set(u32 data) {
    XGpio_DiscreteWrite(p_gpio, 1, data);
    return XST_SUCCESS;
}
