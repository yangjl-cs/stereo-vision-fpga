#include "xstatus.h"
#include "xdebug.h"
#include "xil_printf.h"
#include "xiicps.h"

#include "camera.h"
#include "camera_config.h"

#define CAM_DEV_ADDR 0x3C

Camera::Camera() {
    this->p_iic = &iic;
}

Camera::~Camera() {
}

int Camera::send_byte(uint16_t addr, uint8_t data) {
    u8 SendBuffer[3];
    SendBuffer[0] = (addr >> 8) & 0xff;
    SendBuffer[1] = addr & 0xff;
    SendBuffer[2] = data & 0xff;
    XIicPs_MasterSendPolled(this->p_iic, SendBuffer, 3, CAM_DEV_ADDR);
    return XST_SUCCESS;
}

int Camera::init(u16 device_id, u32 sclk_rate) {
    int status;
    XIicPs_Config *config;
    config = XIicPs_LookupConfig(device_id);
    if (NULL == config) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "Configuration lookup failed %d\r\n", status);
        return XST_FAILURE;
    }
    status = XIicPs_CfgInitialize(this->p_iic, config, config->BaseAddress);
    if (status != XST_SUCCESS) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "Initialization failed %d\r\n", status);
        return XST_FAILURE;
    }
    /*
     * Perform a self-test to ensure that the hardware was built correctly.
     */
    status = XIicPs_SelfTest(this->p_iic);
    if (status != XST_SUCCESS) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "Self-test failed %d\r\n", status);
        return XST_FAILURE;
    }
    /*
     * Set the IIC serial clock rate.
     */
    XIicPs_SetSClk(this->p_iic, sclk_rate);
    return XST_SUCCESS;
}

int Camera::config(u8 camera_id) {
    if (camera_id == CONFIG_OV5640) {
        int length = sizeof(ov5640_config) / sizeof(camera_config_word_t);
        xil_printf("*I*     Camera id: OV5640, configuration data length: %d\n", length);
        for(int i = 0; i < length; i++)
            this->send_byte(ov5640_config[i].addr, ov5640_config[i].data);
        return XST_SUCCESS;
    }
    else {
        xil_printf("*E*     Unknown camera id specified: %d\n", camera_id);
        return XST_FAILURE;
    }
}
