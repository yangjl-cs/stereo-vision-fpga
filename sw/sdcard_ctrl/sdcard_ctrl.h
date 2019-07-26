#ifndef SRC_SDCARD_CTRL_SDCARD_CTRL_H_
#define SRC_SDCARD_CTRL_SDCARD_CTRL_H_

#include "xil_types.h"
#include "ff.h"

class SdCardCtrl {
private:
	FATFS fatfs;
	FATFS *p_fatfs;
public:
	SdCardCtrl();
	~SdCardCtrl();
	int init();
	int transfer_read(char *file_name, u32 dst_addr, u32 byte_len);
	int transfer_write(char *file_name, u32 src_addr, u32 byte_len);
};


#endif /* SRC_SDCARD_CTRL_SDCARD_CTRL_H_ */
