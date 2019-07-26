#include "xstatus.h"
#include "xdebug.h"
#include "xaxivdma.h"

#include "vdma_ctrl.h"

VdmaCtrl::VdmaCtrl() {
    p_vdma = &vdma;
}

VdmaCtrl::~VdmaCtrl() {
}

int VdmaCtrl::init(u16 device_id) {
    int status;
    XAxiVdma_Config *config;
    config = XAxiVdma_LookupConfig(device_id);
    if (NULL == config) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "*E* Cannot get AxiVdma configuration\n");
        return XST_FAILURE;
    }
    status = XAxiVdma_CfgInitialize(this->p_vdma, config, config->BaseAddress);
    if (status != XST_SUCCESS) {
        xdbg_printf(XDBG_DEBUG_GENERAL, "*E* AxiVdma configuration initialization failed\n");
        return XST_FAILURE;
    }
    XAxiVdma_Reset(this->p_vdma, XAXIVDMA_WRITE);
    XAxiVdma_Reset(this->p_vdma, XAXIVDMA_READ);
    return XST_SUCCESS;
}

int VdmaCtrl::stop_read() {
    XAxiVdma_DmaStop(this->p_vdma, XAXIVDMA_READ);
    while (XAxiVdma_IsBusy(this->p_vdma, XAXIVDMA_READ))
        ;
    return XST_SUCCESS;
}

int VdmaCtrl::stop_write() {
    XAxiVdma_DmaStop(this->p_vdma, XAXIVDMA_WRITE);
    while (XAxiVdma_IsBusy(this->p_vdma, XAXIVDMA_WRITE))
        ;
    return XST_SUCCESS;
}

int VdmaCtrl::stop(u8 dir) {
    if (dir == VDMA_DIR_READ) {
        this->stop_read();
        return XST_SUCCESS;
    }
    else if (dir == VDMA_DIR_WRITE) {
        this->stop_write();
        return XST_SUCCESS;
    }
    else if (dir == VDMA_DIR_BOTH) {
        this->stop_read();
        this->stop_write();
        return XST_SUCCESS;
    }
    else {
        return XST_FAILURE;
    }
}


int VdmaCtrl::start_write() {
    int status;
    status = XAxiVdma_DmaStart(this->p_vdma, XAXIVDMA_WRITE);
    return status;
}

int VdmaCtrl::start_read() {
    int status;
    status = XAxiVdma_DmaStart(this->p_vdma, XAXIVDMA_READ);
    return status;
}

int VdmaCtrl::start(u8 dir) {
    int status;
    if (dir == VDMA_DIR_READ) {
        status = this->start_read();
        return status;
    }
    else if (dir == VDMA_DIR_WRITE) {
        status = this->start_write();
        return status;
    }
    else if (dir == VDMA_DIR_BOTH) {
        status = this->start_read();
        if (status == XST_SUCCESS) {
            status = this->start_write();
        }
        return status;
    }
    else {
        return XST_FAILURE;
    }
}


int VdmaCtrl::setup(u8 dir, u32 base_addr, u32 pixel_byte, u32 hori_size, u32 vert_size, u32 hori_stride, u32 vert_stride) {
    XAxiVdma_DmaSetup config;

    config.VertSizeInput = vert_size;
    config.HoriSizeInput = hori_size * pixel_byte;
    config.Stride = hori_stride * pixel_byte;

    config.FrameDelay = 1;
    config.EnableCircularBuf = 1;
    config.EnableSync = 1;
    config.PointNum = 0;
    config.EnableFrameCounter = 0;
    config.FixedFrameStoreAddr = 0;

    // int block_offset;
    // block_offset = (hori_stride * pixel_byte) * VertOffset;
    // block_offset += (HoriOffset * pixel_byte);

    // Initialize buffer addresses
    for (int i= 0; i < 3; i++) {
        // ReadCfg.FrameStoreStartAddr[i] = base_addr + block_offset;
        config.FrameStoreStartAddr[i] = base_addr;
        base_addr += hori_stride * pixel_byte * vert_stride;
    }

    if (dir == VDMA_DIR_READ) {
        XAxiVdma_DmaConfig(this->p_vdma, XAXIVDMA_READ, &config);
        XAxiVdma_DmaSetBufferAddr(this->p_vdma, XAXIVDMA_READ, config.FrameStoreStartAddr);
        return XST_SUCCESS;
    }
    else if (dir == VDMA_DIR_WRITE) {
        XAxiVdma_DmaConfig(this->p_vdma, XAXIVDMA_WRITE, &config);
        XAxiVdma_DmaSetBufferAddr(this->p_vdma, XAXIVDMA_WRITE, config.FrameStoreStartAddr);
        return XST_SUCCESS;
    }
    else if (dir == VDMA_DIR_BOTH) {
        XAxiVdma_DmaConfig(this->p_vdma, XAXIVDMA_READ, &config);
        XAxiVdma_DmaSetBufferAddr(this->p_vdma, XAXIVDMA_READ, config.FrameStoreStartAddr);
        XAxiVdma_DmaConfig(this->p_vdma, XAXIVDMA_WRITE, &config);
        XAxiVdma_DmaSetBufferAddr(this->p_vdma, XAXIVDMA_WRITE, config.FrameStoreStartAddr);
        return XST_SUCCESS;
    }
    else {
        return XST_FAILURE;
    }
}
