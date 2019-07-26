#include "stereovision.h"
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
#include "hls_opencv.h"

#define INPUT_IMAGE_L "./img/left.bmp"
#define INPUT_IMAGE_R "./img/right.bmp"
#define OUTPUT_IMAGE "./img/result.bmp"

int main (int argc, char** argv) {
	// Load data in OpenCV image format
    IplImage* srcl = cvLoadImage(INPUT_IMAGE_L, CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* srcr = cvLoadImage(INPUT_IMAGE_R, CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* dst = cvCreateImage(cvGetSize(srcl), IPL_DEPTH_8U, 1);

    AXIS8 srcl_axi;
    AXIS8 srcr_axi;
    AXIS8 dst_axi;

    // Convert OpenCV format to AXI4 Stream format
    IplImage2AXIvideo(srcl, srcl_axi);
    IplImage2AXIvideo(srcr, srcr_axi);

    stereo_vision(srcl_axi, srcr_axi, dst_axi, srcl->height, srcl->width);

    // Convert the AXI4 Stream data to OpenCV format
    AXIvideo2IplImage(dst_axi, dst);

    cvSaveImage(OUTPUT_IMAGE, dst);
    cvReleaseImage(&srcl);
    cvReleaseImage(&dst);
    cvReleaseImage(&srcr);
}
