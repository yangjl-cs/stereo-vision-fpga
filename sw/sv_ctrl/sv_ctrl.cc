#include "xil_types.h"
#include "xdebug.h"
#include "xstatus.h"

#include "sv_ctrl.h"
#include "xstereo_vision.h"

StereoVisionCtrl::StereoVisionCtrl(){
    p_sv = &sv;
}

StereoVisionCtrl::~StereoVisionCtrl(){
}

int StereoVisionCtrl::init(u16 device_id){
    int status;
    XStereo_vision_Config *config;
    config = XStereo_vision_LookupConfig(device_id);
    if (NULL == config) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "*E* Cannot get StereoVision configuration\n");
        return XST_FAILURE;
    }
    status = XStereo_vision_CfgInitialize(this->p_sv, config);
    if (status != XST_SUCCESS) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "*E* StereoVision configuration initialization failed\n");
        return XST_FAILURE;
    }
    return XST_SUCCESS;
}

int StereoVisionCtrl::set_size(u32 width, u32 height){
    XStereo_vision_Set_rows(this->p_sv, height);
    XStereo_vision_Set_cols(this->p_sv, width);
    return XST_SUCCESS;
}

//int StereoVisionCtrl::set_src(u8 dir){
//	if (dir == CAMERA_SRC_LEFT) {
//      XStereo_vision_Set_Ctrl(this->p_sv, 0);
//	}
//	else {
//		XStereo_vision_Set_Ctrl(this->p_sv, 1);
//	}
//	return XST_SUCCESS;
//}
