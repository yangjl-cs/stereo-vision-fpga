#ifndef _STEREOVISION_H_
#define _STEREOVISION_H_

#include "hls_video.h"

#define MAX_WIDTH 1280
#define MAX_HEIGHT 720

typedef hls::stream<ap_axiu<24,1,1,1> > AXIS24;
typedef hls::stream<ap_axiu<8,1,1,1> > AXIS8;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> IMG_RGB;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC1> IMG_GRAY;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_16SC1> IMG_DISP;
typedef hls::StereoBMState<15, 128, 16> BM_STATE;

void stereo_vision(AXIS8 &vid_inL, AXIS8 &vid_inR, AXIS8 &vid_out, int rows, int cols);

#endif // _STEREOVISION_H_
