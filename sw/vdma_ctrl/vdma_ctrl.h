#ifndef SRC_VDMA_CTRL_VDMA_CTRL_H_
#define SRC_VDMA_CTRL_VDMA_CTRL_H_

#include "xaxivdma.h"

#define VDMA_DIR_BOTH  0
#define VDMA_DIR_READ  1
#define VDMA_DIR_WRITE 2

class VdmaCtrl {
private:
    XAxiVdma vdma;
    XAxiVdma *p_vdma;
    int start_read();
    int start_write();
    int stop_read();
    int stop_write();
public:
    VdmaCtrl();
    ~VdmaCtrl();
    int init(u16 device_id);
    int setup(u8 dir, u32 base_addr, u32 pixel_byte, u32 hori_size, u32 vert_size, u32 hori_stride, u32 vert_stride);
    int start(u8 dir);
    int stop(u8 dir);
};


#endif /* SRC_VDMA_CTRL_VDMA_CTRL_H_ */
