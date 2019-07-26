#ifndef SRC_SV_CTRL_SV_CTRL_H_
#define SRC_SV_CTRL_SV_CTRL_H_

#include "xil_types.h"

#include "xstereo_vision.h"

#define CAMERA_SRC_LEFT  0
#define CAMERA_SRC_RIGHT 1

class StereoVisionCtrl {
private:
    XStereo_vision sv;
    XStereo_vision *p_sv;
public:
    StereoVisionCtrl();
    ~StereoVisionCtrl();
    int init(u16 device_id);
    int set_size(u32 width, u32 height);
    // int set_src(u8 dir);
};

#endif /* SRC_SV_CTRL_SV_CTRL_H_ */
