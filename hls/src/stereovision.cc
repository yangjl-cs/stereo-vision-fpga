#include "hls_video.h"

#include "stereovision.h"
#include "camera_param.h"

// A integer version of hls::ConvertScaleAbs
void ConvertShiftAbs(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_16SC1>& _src,
    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC1>& _dst){
    hls::Scalar<1, short> _s;
    hls::Scalar<1, unsigned char> _d;
    loop_height: for(int i= 0;i<MAX_HEIGHT;i++) {
		loop_width: for (int j= 0;j<MAX_WIDTH;j++) {
	    #pragma HLS LOOP_FLATTEN OFF
	    #pragma HLS PIPELINE
			_src>>_s;
			_d.val[0]=(unsigned char)(abs(_s.val[0] >> 4));
			_dst<<_d;
		}
	}
}

void stereo_vision(AXIS8 &vid_inL, AXIS8 &vid_inR, AXIS8 &vid_out, int rows, int cols) {
#pragma HLS INTERFACE s_axilite port=cols bundle=Ctrl
#pragma HLS INTERFACE s_axilite port=rows bundle=Ctrl
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis register port=vid_out
#pragma HLS INTERFACE axis register port=vid_inR
#pragma HLS INTERFACE axis register port=vid_inL
#pragma HLS DATAFLOW

	hls::Window<3, 3, ap_fixed<32,12> > PAR_L_CAMM;
	hls::Window<3, 3, ap_fixed<32,12> > PAR_R_CAMM;
	hls::Window<3, 3, ap_fixed<32,2> > PAR_L_RM;
	hls::Window<3, 3, ap_fixed<32,1> > PAR_R_RM;

	PAR_L_CAMM.val[0][0] = PAR_L_CAMM_RAW[0];
	PAR_L_CAMM.val[0][1] = PAR_L_CAMM_RAW[1];
	PAR_L_CAMM.val[0][2] = PAR_L_CAMM_RAW[2];
	PAR_L_CAMM.val[1][0] = PAR_L_CAMM_RAW[3];
	PAR_L_CAMM.val[1][1] = PAR_L_CAMM_RAW[4];
	PAR_L_CAMM.val[1][2] = PAR_L_CAMM_RAW[5];
	PAR_L_CAMM.val[2][0] = PAR_L_CAMM_RAW[6];
	PAR_L_CAMM.val[2][1] = PAR_L_CAMM_RAW[7];
	PAR_L_CAMM.val[2][2] = PAR_L_CAMM_RAW[8];

	PAR_R_CAMM.val[0][0] = PAR_R_CAMM_RAW[0];
	PAR_R_CAMM.val[0][1] = PAR_R_CAMM_RAW[1];
	PAR_R_CAMM.val[0][2] = PAR_R_CAMM_RAW[2];
	PAR_R_CAMM.val[1][0] = PAR_R_CAMM_RAW[3];
	PAR_R_CAMM.val[1][1] = PAR_R_CAMM_RAW[4];
	PAR_R_CAMM.val[1][2] = PAR_R_CAMM_RAW[5];
	PAR_R_CAMM.val[2][0] = PAR_R_CAMM_RAW[6];
	PAR_R_CAMM.val[2][1] = PAR_R_CAMM_RAW[7];
	PAR_R_CAMM.val[2][2] = PAR_R_CAMM_RAW[8];

	PAR_L_RM.val[0][0] = PAR_L_RM_RAW[0];
	PAR_L_RM.val[0][1] = PAR_L_RM_RAW[1];
	PAR_L_RM.val[0][2] = PAR_L_RM_RAW[2];
	PAR_L_RM.val[1][0] = PAR_L_RM_RAW[3];
	PAR_L_RM.val[1][1] = PAR_L_RM_RAW[4];
	PAR_L_RM.val[1][2] = PAR_L_RM_RAW[5];
	PAR_L_RM.val[2][0] = PAR_L_RM_RAW[6];
	PAR_L_RM.val[2][1] = PAR_L_RM_RAW[7];
	PAR_L_RM.val[2][2] = PAR_L_RM_RAW[8];

	PAR_R_RM.val[0][0] = PAR_R_RM_RAW[0];
	PAR_R_RM.val[0][1] = PAR_R_RM_RAW[1];
	PAR_R_RM.val[0][2] = PAR_R_RM_RAW[2];
	PAR_R_RM.val[1][0] = PAR_R_RM_RAW[3];
	PAR_R_RM.val[1][1] = PAR_R_RM_RAW[4];
	PAR_R_RM.val[1][2] = PAR_R_RM_RAW[5];
	PAR_R_RM.val[2][0] = PAR_R_RM_RAW[6];
	PAR_R_RM.val[2][1] = PAR_R_RM_RAW[7];
	PAR_R_RM.val[2][2] = PAR_R_RM_RAW[8];

    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_16SC2> hmap1L(rows, cols);
    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_16UC2> hmap2L(rows, cols);
    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_16SC2> hmap1R(rows, cols);
    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_16UC2> hmap2R(rows, cols);

    BM_STATE bm_state;
    // bm_state.preFilterType = HLS_STEREO_BM_NORMALIZED_RESPONSE;

    IMG_GRAY imgL_in(rows, cols);
    IMG_GRAY imgR_in(rows, cols);

    IMG_GRAY imgL_rmap(rows, cols);
    IMG_GRAY imgR_rmap(rows, cols);

    IMG_DISP img_disp(rows, cols);
    IMG_GRAY img_disp8u(rows, cols);

    IMG_GRAY img_erode(rows, cols);
    IMG_GRAY img_dilate(rows, cols);

    hls::AXIvideo2Mat(vid_inL, imgL_in);
    hls::AXIvideo2Mat(vid_inR, imgR_in);

    hls::InitUndistortRectifyMapInverse(PAR_L_CAMM, PAR_L_DISTC, PAR_L_RM, hmap1L, hmap2L);
    hls::Remap<16>(imgL_in, imgL_rmap, hmap1L, hmap2L, HLS_INTER_LINEAR);

    hls::InitUndistortRectifyMapInverse(PAR_R_CAMM, PAR_R_DISTC, PAR_R_RM, hmap1R, hmap2R);
    hls::Remap<16>(imgR_in, imgR_rmap, hmap1R, hmap2R, HLS_INTER_LINEAR);

    hls::FindStereoCorrespondenceBM(imgL_rmap, imgR_rmap, img_disp, bm_state);

    ConvertShiftAbs(img_disp, img_disp8u);
	hls::Erode(img_disp8u, img_erode);
	hls::Dilate(img_erode, img_dilate);

    hls::Mat2AXIvideo(img_dilate, vid_out);

    return;
}
