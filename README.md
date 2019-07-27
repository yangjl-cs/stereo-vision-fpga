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

## Contributors
- Haozhe Zhu ([@zhutmost](https://github.com/zhutmost))
- Jinglei Yang ([@MsYangjl](https://github.com/MsYangjl))
- Liyu Lin ([@lylinsh](https://github.com/lylinsh))
- Yinfei Pan

This is an open-source project, so if you want to contribute, just open issues and create pull-requests.
