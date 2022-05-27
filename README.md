# Binocular Stereo Vision FPGA System

This project implements a binocular stereo vision system on an FPGA platform. It uses a binocular module to capture images from different positions, caculates the positional deviation between the corresponding points in these two images, and outputs the diparity diagram and the depth information on a HDMI monitor.

This project is originally designed for a student contest in the 2019 SEU-Xilinx International Summer School.

Sincere appreciation to Xilinx for sponsoring this project.

## Quick Instructions

Here are instructions about how to setup this stereo vision system on your FPGA board.

### Prerequisites

- Xilinx Vivado (including SDK & HLS) 2018.2
- PYNQ-Z2 Development Board
- A binocular vision module with two OV5640 cameras
- A HDMI monitor

This project is developed and tested with Xilinx Vivado Suite 2018.2, but it *should* work with newer versions.

The PYNQ operating system is not used in this project, so you can port this project to other ZYNQ platforms at will.

This PYNQ-Z2 board has only two PMOD interfaces, so we connect the FPGA with the binocular module by the Raspberry PI GPIOs.

### Generate HLS IPs

The stereo vision component is written in Vivado HLS, so please follow these steps to generate and export the IP core.

All the relevant HLS C++ files can be found in `\$REPO_PATH/hls/src`.

A Tcl script named `make.tcl` is included in `\$REPO_PATH/hls`. You can use `vivado_hls` to execute it in the Vivado HLS Prompt.

```tcl
vivado_hls $REPO_PATH/hls/make.tcl
```

This project will create a HLS project in `\$REPO_PATH/work/sv_hls`, and you need to extract the exported IP to the IP repository folder (`\$REPO_PATH/ip_repo`). The following Vivado building scripts will search for third-part and user-defined IP cores in this folder.

### Build Vivado Project

You can "source" scripts in your Vivado Tcl Console to build the Vivado project. These scripts will import RTL files, third-part IPs, SDK C++ files and other necessary files.

```tcl
set argv [list project=sv_fpga sdk=yes version_override=yes]
set argc [llength $argv]
source "$REPO_PATH/hw/make.tcl" -notrace
```
Due to the maximum path length limitation on Windows (<260), do NOT specify a very long project name.
The default building path is `\$REPO_PATH/work/\$PROJ_NAME`.

### Citation
if this paper is useful for you, please quote as below.

Gang Wu, Jinglei Yang, Hao Yang: Real-time low-power binocular stereo vision based on FPGA. J. Real Time Image Process. 19(1): 29-39 (2022)


### References

1.Adams, J.K., Thomas, D.E.: The design of mixed hardware/software systems. In: Proceedings of the 33rd annual Design Automation Conference (DAC’96). Association for Computing Machinery, New York, NY, USA, pp515–520. (1996) https://doi.org/10.1145/240518.240616

2.Ambrosch, K., Humenberger, M., Kubinger, W., Steininger, A.:SAD-Based stereo matching using FPGAs. In: Kisačanin, B.,Bhattacharyya, S.S., Chai, S. (eds.) Embedded Computer Vision.Advances in Pattern Recognition. Springer, London, pp.121-138. https://doi.org/10.1007/978-1-84800-304-0_6 

3.Finnerty, A., Ratigner, H.: Reduce Power andCost by Converting from Floating Point to FixedPoint, WP491 (v1.0). Xilinx (2017). https://www.xilinx.com/support/docum entation/white_papers/wp491-floating-to-fixed-point.pdf

4.Angoletta, M.E.: Digital signal processor fundamentals and system design. In : CAS-CERN Accelerator School: Digital Signal Processing,pp.167–229 (2008)

5.Bouguet, J.Y.: Fifth calibration example - calibrating a stereo system, stereo image rectification and 3d stereo triangulation.http://www.vision.caltech.edu/bougu etj/calib_doc/htmls/example5.html

6.Bouguet, J.Y.: Camera calibration toolbox for matlab (2015).http://www.vision.caltech.edu/bouguetj/calib_doc/

7.Crockett, L.H., Elliot, R.A., Enderwitz, M.A., Stewart, R.W.: TheZynq Book: Embedded Processing with the Arm Cortex-A9 on the Xilinx Zynq-7000 All Programmable Soc. Strathclyde Academic Media, Glasgow (2014)

8.DeMicheli, G., Sami, M.: Hardware/software Co-design,. Springer Science & Business Media, Berlin 310 (2013)

9.Einspruch, N.: Application Specific Integrated Circuit (ASIC)Technology, vol. 23. Academic Press, Cambridge (2012)
10.Fetić, A., Jurić, D., Osmanković, D.: The procedure of a camera calibration using Camera Calibration Toolbox for MATLAB, In:Proceedings of the 35th International Convention MIPRO, pp.1752-1757(2012)

11.Geiger, A., Roser, M., Urtasun, R.: Efficient Large-Scale Stereo Matching. In: Kimmel, R., Klette, R., Sugimoto, A. (eds.) Computer Vision – ACCV 2010. Lecture Notes in Computer Science,vol.6492. Springer, Berlin, Heidelberg.(2011). https://doi.org/10.1007/978-3-642-19315-6_3

12.Guo, Y., Yao, Y., Di, X.: Research on Structural Parameter Optimization of Binocular Vision Measuring System for Parallel Mechanism. In: 2006 International Conference on Mechatronics and Automation, pp. 1131-1135 (2006) https://doi.org/10.1109/ICMA.2006.257784

13.Jin, S., Cho, J., Dai Pham, X., Lee, K.M., Park, S.K., Kim, M.,Jeon, J.W.: Fpga design and implementation of a real-time stereo vision system. IEEE Trans. Circuits Syst. Video Technol. 20(1),15–26(2009)

14.Li, J., Wu, J., You, Y., Jeon, G.: Parallel binocular stereo-visionbased gpu accelerated pedestrian detection and distance computation.J. Real-Time Image Process. 17(3), 447–457(2020)

15.Lin, C.Y., Chiu, Y.P., Lin, C.Y., Tsai, C.R.: Development of a binocular vision-based catcher robot system using dsp platform. J. Chin. Inst. Eng. 37(2), 210–223 (2014)

16.Madisetti, V., Madisetti, V.: VLSI Digital Signal Processors. Butterworth-Heinemann, Oxford (1995)

17.Mahammed, M.A., Melhum, A.I., Kochery, F.A.: Object distance measurement by stereo vision. Int. J. Sci. Appl. Inform. Technol.(IJSAIT) 2(2), 05–08 (2013)
18.Nan, Y.: Binocular vision system based on pynq (2017). http://www.digilent.com.cn/project/details/140.html

19.Pan, Y., Zhu, M., Luo, J., Qiu, Y.: A Hardware/Software Codesign Approach for Real-Time Binocular Stereo Vision Based on ZYNQ (Short Paper). In: Gao, H., Wang, X., Yin, Y., Iqbal, M. (eds) Collaborative Computing: Networking, Applications and Worksharing. CollaborateCom 2018. Lecture Notes of the Institute for Computer Sciences, Social Informatics and Telecommunications Engineering, vol. 268. Springer, Cham (2019). https://doi.org/10.1007/978-3-030-12981-1_50

20.Pérez-Patricio, M., Aguilar-González, A.: Fpga implementation of an efficient similarity-based adaptive window algorithm for realtime stereo matching. J. Real-Time Image Process. 16(2), 271–287 (2019)
21.Perri, S., Frustaci, F., Spagnolo, F., Corsonello, P.: Design of Real-Time FPGA-based Embedded System for Stereo Vision. In: 2018 IEEE International Symposium on Circuits and Systems (ISCAS),pp. 1–5 (2018).https://doi.org/10.1109/ISCAS.2018.8351886

22.Rahnama, O., Cavallari, T., Golodetz, S., Tonioni, A., Joy, T., Di Stefano, L., Walker, S., Torr, P.H.: Real-time highly accurate dense depth on a power budget using an fpga-cpu hybrid soc.IEEE Trans. Circ. Syst. II 66(5),773–777(2019)

23.Rodriguez-Andina, J.J., Moure, M.J., Valdes, M.D.: Features, design tools, and application domains of fpgas. IEEE Trans. Ind.Electron.54(4),1810–1823(2007)

24.Salmen, J., Schlipsing, M., Edelbrunner, J., Hegemann, S., Lüke, S.: Real-time stereo vision: making more out of dynamic programming. In: International Conference on Computer Analysis of Images and Patterns,pp. 1096–1103.Springer(2009)

25.Scharstein, D., Szeliski, R.:A taxonomy and evaluation of dense two-frame stereo correspondence algorithms. Int.J.Comput.Vis.47(1),7–42(2002)

26.Schauwecker, K.: Real-Time Stereo Visionon FPGAs with SceneScan (2018).CoRRabs/1809.07977

27.Tang, Y., Pang, C., Zhou, Z., Chen, Y.: Binocularomni-directional vision sensor and epipolar rectification in its omni-directional images.J. Zhejiang Univ. Technol. 1,20 (2011)

28.Werner, M., Stabernack, B., Riechert, C.: Hardware implementation of a full hd real-time disparity estimation algorithm. IEEE Trans. Consumer Electron. 60(1),66–73 (2014)

29.Yan, Y., Zhu, Q., Lin, Z., Chen, Q.: Camera Calibration in Binocular Stereo Vision of Moving Robot. In: 2006 6th World Congress on Intelligent Control and Automation,pp. 9257–9261. https://doi.org/10.1109/WCICA.2006.1713792

30.Zhang, K., Lu, J., Lafruit, G., Lauwereins, R., Gool, L.V.: Realtime accurate stereo with bitwise fast voting on CUDA. In: 2009 IEEE 12th International Conference on Computer Vision Workshops, ICCVWorkshops,pp.794-800(2009). https://doi.org/10.1109/ICCVW.2009.5457623

31.Zhang, Z.: A flexible new technique for camera calibration. IEEETrans. Pattern Anal.Mach.Intell.22(11),1330–1334(2000)

## Contributors
- Jinglei Yang ([@MsYangjl](https://github.com/MsYangjl))
- Haozhe Zhu ([@zhutmost](https://github.com/zhutmost))
- Liyu Lin ([@lylinsh](https://github.com/lylinsh))
- Yinfei Pan

This is an open-source project, so if you want to contribute, just open issues and create pull-requests.
