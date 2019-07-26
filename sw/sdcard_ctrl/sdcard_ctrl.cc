#include "xstatus.h"
#include "xil_printf.h"
#include "ff.h"

#include "sdcard_ctrl.h"

SdCardCtrl::SdCardCtrl(){
    p_fatfs = &fatfs;
}

SdCardCtrl::~SdCardCtrl(){}

int SdCardCtrl::init() {
    FRESULT f_result;
    f_result = f_mount(p_fatfs, "0:/", 0);
    if(f_result) {
        xil_printf("*E* Cannot mount SD Card (code: %d)\n", f_result);
        return XST_FAILURE;
    }
    return XST_SUCCESS;
}

int SdCardCtrl::transfer_read(char* file_name, u32 dst_addr, u32 byte_len) {
    FIL fil;
    FRESULT f_result;
    UINT br;

    f_result = f_open(&fil, file_name, FA_READ);
    if(f_result) {
        xil_printf("*E* Cannot open file (code: %d)\n", f_result);
        return XST_FAILURE;
    }

    f_result = f_lseek(&fil, 0);
    if(f_result) {
        xil_printf("*E* f_lseek failed (code: %d)\n", f_result);
        return XST_FAILURE;
    }

    f_result = f_read(&fil, (void*)dst_addr, byte_len, &br);
    if(f_result) {
        xil_printf("*E* f_read failed (code: %d)\n", f_result);
        return XST_FAILURE;
    }

    f_result = f_close(&fil);
    if(f_result) {
        xil_printf(" *E* Cannot close file (code: %d)\n", f_result);
        return XST_FAILURE;
    }
    return XST_SUCCESS;
}

int SdCardCtrl::transfer_write(char *file_name, u32 src_addr, u32 byte_len) {
    FIL fil;
    FRESULT f_result;
    UINT bw;

    f_result = f_open(&fil, file_name, FA_CREATE_ALWAYS | FA_WRITE);
    if( f_result) {
        xil_printf("*E* Cannot open file (code: %d)\n", f_result);
        return XST_FAILURE;
    }

     f_result = f_lseek(&fil, 0);
    if( f_result) {
        xil_printf("*E* f_lseek failed (code: %d)\n", f_result);
        return XST_FAILURE;
    }

     f_result = f_write(&fil, (void*) src_addr, byte_len, &bw);
    if( f_result) {
        xil_printf("*E* f_write failed (code: %d)\n",  f_result);
        return XST_FAILURE;
    }

    f_result = f_sync(&fil);
    if( f_result) {
        xil_printf("*E* f_sync failed (code: %d)\n", f_result);
        return XST_FAILURE;
    }

     f_result = f_close(&fil);
    if( f_result) {
        xil_printf("*E* Cannot close file (code: %d)\n", f_result);
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}
