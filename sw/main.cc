#include "xparameters.h"
#include "xil_printf.h"
#include "xv_demosaic.h"
#include "sleep.h"

#include "camera/camera.h"
// #include "dynclk_ctrl/dynclk_ctrl.h"
#include "gpio/led.h"
// #include "vtc_ctrl/vtc_ctrl.h"
#include "vdma_ctrl/vdma_ctrl.h"
#include "sv_ctrl/sv_ctrl.h"
#include "sdcard_ctrl/sdcard_ctrl.h"
#include "vga_mode.h"

#define IIC_SCLK_RATE 100000

#define FRAME_BUF_L 0x01000000
#define FRAME_BUF_R 0x06000000
#define FRAME_BUF_O 0x0b000000

int main() {
    int status;
    xil_printf("*I* <Stereo Vision System>\n");
    

    xil_printf("*I* === === Configuration === ===\n");

    xil_printf("*I* --> Demosaic\n");
    XV_demosaic *p_demosaic_l = new XV_demosaic;
    XV_demosaic *p_demosaic_r = new XV_demosaic;
    XV_demosaic_Initialize(p_demosaic_l, XPAR_SENSOR2GRAY_L_DEMOSAIC_DEVICE_ID);
    XV_demosaic_Initialize(p_demosaic_r, XPAR_SENSOR2GRAY_R_DEMOSAIC_DEVICE_ID);

    XV_demosaic_Set_HwReg_width(p_demosaic_l, 1280);
    XV_demosaic_Set_HwReg_height(p_demosaic_l, 720);
    XV_demosaic_Set_HwReg_bayer_phase(p_demosaic_l, 1);
    XV_demosaic_EnableAutoRestart(p_demosaic_l);
    XV_demosaic_Start(p_demosaic_l);

    XV_demosaic_Set_HwReg_width(p_demosaic_r, 1280);
    XV_demosaic_Set_HwReg_height(p_demosaic_r, 720);
    XV_demosaic_Set_HwReg_bayer_phase(p_demosaic_r, 1);
    XV_demosaic_EnableAutoRestart(p_demosaic_r);
    XV_demosaic_Start(p_demosaic_r);

    xil_printf("*I* --> Camera I2C\n");
    Camera p_cam_l, p_cam_r;
    p_cam_l.init(XPAR_PS7_I2C_0_DEVICE_ID, IIC_SCLK_RATE);
    p_cam_r.init(XPAR_PS7_I2C_1_DEVICE_ID, IIC_SCLK_RATE);
    p_cam_l.config(CONFIG_OV5640);
    p_cam_r.config(CONFIG_OV5640);

    // VideoMode vid_mode = VMODE_1280x720;

    // xil_printf("*I* --> Dynamic Clock Generator\n");
    // DynclkCtrl p_dynclk;
    // status = p_dynclk.init(XPAR_AXI_DYNCLK_0_BASEADDR, vid_mode.freq);
    // status = p_dynclk.start(vid_mode.freq);

    xil_printf("*I* --> VDMA (vid_in & vid_out)\n");
    VdmaCtrl p_vdma_l, p_vdma_r, p_vdma_o;
    status = p_vdma_l.init(XPAR_VDMA_L_DEVICE_ID);
    status = p_vdma_r.init(XPAR_VDMA_R_DEVICE_ID);
    status = p_vdma_o.init(XPAR_VDMA_O_DEVICE_ID);
    status = p_vdma_l.setup(VDMA_DIR_BOTH, FRAME_BUF_L, 1, 1280, 720, 4096, 2048);
    status = p_vdma_r.setup(VDMA_DIR_BOTH, FRAME_BUF_R, 1, 1280, 720, 4096, 2048);
    status = p_vdma_o.setup(VDMA_DIR_BOTH, FRAME_BUF_O, 1, 1280, 720, 4096, 2048);

    // xil_printf("*I* --> Video Timing Controller\n");
    // VtcCtrl p_vtc;
    // p_vtc.init(XPAR_VTC_0_DEVICE_ID);
    // p_vtc.start();

    xil_printf("*I* --> Stereo Vision Controller\n");
    StereoVisionCtrl p_sv;
    p_sv.init(XPAR_STEREO_VISION_DEVICE_ID);
    p_sv.set_size(1280, 720);
    // p_sv.set_src(CAMERA_SRC_LEFT);

    xil_printf("*I* --> SD File System\n");
    SdCardCtrl p_sdcard;
    status = p_sdcard.init();

    xil_printf("*I* --> LEDs\n");
    Led p_led;
    p_led.init(XPAR_GPIO_LED_DEVICE_ID);

    xil_printf("*I* === === Running === ===\n");

    status = p_vdma_l.start(VDMA_DIR_BOTH);
    status = p_vdma_r.start(VDMA_DIR_BOTH);
    status = p_vdma_o.start(VDMA_DIR_BOTH);

    // for (int i = 0; i < 10; i ++) {
    //  // sleep(1);
    // 	// p_sv.set_src(CAMERA_SRC_RIGHT);
    // 	// sleep(1);
    // 	// p_sv.set_src(CAMERA_SRC_LEFT);
    //  sleep(1);
    // 	status = p_vdma_l.stop(VDMA_DIR_BOTH);
    // 	status = p_vdma_r.stop(VDMA_DIR_BOTH);
    // 	char *fname_l = "0:/lx.img";
    // 	char *fname_r = "0:/rx.img";
    // 	fname_l[4] = '0' + i;
    // 	fname_r[4] = '0' + i;
    // 	status = p_sdcard.transfer_write(fname_l, FRAME_BUF_L, 4096*4096);
    // 	status = p_sdcard.transfer_write(fname_r, FRAME_BUF_R, 4096*4096);
    // 	status = p_vdma_l.start(VDMA_DIR_BOTH);
    // 	status = p_vdma_r.start(VDMA_DIR_BOTH);
    // }

    // status = p_vdma_l.stop(VDMA_DIR_BOTH);
    // status = p_vdma_r.stop(VDMA_DIR_BOTH);
    // status = p_vdma_o.stop(VDMA_DIR_BOTH);

    return 0;
}
