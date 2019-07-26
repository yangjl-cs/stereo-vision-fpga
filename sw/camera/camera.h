#ifndef SRC_CAMERA_CAMERA_H_
#define SRC_CAMERA_CAMERA_H_

#include "xiicps.h"

#define CONFIG_OV5640 0

class Camera {
private:
    XIicPs iic;
    XIicPs *p_iic;
    int send_byte(uint16_t addr, uint8_t data);
public:
    Camera();
    ~Camera();
    int init(u16 device_id, u32 sclk_rate);
    int config(u8 camera_id);
};

#endif /* SRC_CAMERA_CAMERA_H_ */
