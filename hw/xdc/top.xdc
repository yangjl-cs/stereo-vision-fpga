#Raspberry Digital I/O

set_property -dict { PACKAGE_PIN W19   IOSTANDARD LVCMOS33 } [get_ports { vid_l_vsync }]; #03-05 CAM0_SCL
set_property -dict { PACKAGE_PIN W18   IOSTANDARD LVCMOS33 } [get_ports { vid_l_iic_scl }]; #02-03 CAM0_SDA
set_property -dict { PACKAGE_PIN Y18   IOSTANDARD LVCMOS33 } [get_ports { vid_l_hsync }]; #04-07 CAM0_VSYNC
set_property -dict { PACKAGE_PIN V6    IOSTANDARD LVCMOS33 } [get_ports { vid_l_iic_sda }]; #14-08 CAM0_HREF
set_property -dict { PACKAGE_PIN U7    IOSTANDARD LVCMOS33 } [get_ports { vid_l_rst }]; #17-11 CAM0_PCLK
set_property -dict { PACKAGE_PIN Y6    IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[0] }]; #15-10 CAM0_XCLK
set_property -dict { PACKAGE_PIN V7    IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[1] }]; #27-13 CAM0_D7
set_property -dict { PACKAGE_PIN C20   IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[2] }]; #18-12 CAM0_D6
set_property -dict { PACKAGE_PIN U8    IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[3] }]; #22-15 CAM0_D5
set_property -dict { PACKAGE_PIN W6    IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[4] }]; #23-16 CAM0_D4
set_property -dict { PACKAGE_PIN V8    IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[5] }]; #10-19 CAM0_D3
set_property -dict { PACKAGE_PIN Y7    IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[6] }]; #24-18 CAM0_D2
set_property -dict { PACKAGE_PIN V10   IOSTANDARD LVCMOS33 } [get_ports { vid_l_data[7] }]; #09-21 CAM0_D1
set_property -dict { PACKAGE_PIN F20   IOSTANDARD LVCMOS33 } [get_ports { vid_l_pclk }]; #25-22 CAM0_D0

set_property -dict { PACKAGE_PIN Y17   IOSTANDARD LVCMOS33 } [get_ports { vid_r_vsync }]; #SC-28 CAM1_SCL
set_property -dict { PACKAGE_PIN Y16   IOSTANDARD LVCMOS33 } [get_ports { vid_r_iic_scl }]; #SD-27 CAM1_SDA
set_property -dict { PACKAGE_PIN W10   IOSTANDARD LVCMOS33 } [get_ports { vid_r_hsync }]; #11-23 CAM1_VSYNC
set_property -dict { PACKAGE_PIN F19   IOSTANDARD LVCMOS33 } [get_ports { vid_r_iic_sda }]; #08-24 CAM1_HREF
set_property -dict { PACKAGE_PIN Y19   IOSTANDARD LVCMOS33 } [get_ports { vid_r_rst }]; #05-29 CAM1_PCLK
set_property -dict { PACKAGE_PIN U19   IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[0] }]; #07-26 CAM1_XCLK
set_property -dict { PACKAGE_PIN U18   IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[1] }]; #06-31 CAM1_D7
set_property -dict { PACKAGE_PIN B20   IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[2] }]; #12-32 CAM1_D6
set_property -dict { PACKAGE_PIN W8    IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[3] }]; #13-33 CAM1_D5
set_property -dict { PACKAGE_PIN B19   IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[4] }]; #16-36 CAM1_D4
set_property -dict { PACKAGE_PIN Y8    IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[5] }]; #19-35 CAM1_D3
set_property -dict { PACKAGE_PIN A20   IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[6] }]; #20-38 CAM1_D2
set_property -dict { PACKAGE_PIN W9    IOSTANDARD LVCMOS33 } [get_ports { vid_r_data[7] }]; #26-37 CAM1_D1
set_property -dict { PACKAGE_PIN Y9    IOSTANDARD LVCMOS33 } [get_ports { vid_r_pclk }]; #21-40 CAM1_D0

set_property PULLUP true [get_ports vid_l_iic_scl]
set_property PULLUP true [get_ports vid_l_iic_sda]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets vid_l_pclk_IBUF]
set_property PULLUP true [get_ports vid_r_iic_scl]
set_property PULLUP true [get_ports vid_r_iic_sda]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets vid_r_pclk_IBUF]

##HDMI Tx

#set_property -dict { PACKAGE_PIN G15   IOSTANDARD LVCMOS33 } [get_ports { hdmi_tx_cec }]; #IO_L19N_T3_VREF_35 Sch=hdmi_tx_cec
set_property -dict { PACKAGE_PIN L17   IOSTANDARD TMDS_33  } [get_ports { TMDS_clk_n }]; #IO_L11N_T1_SRCC_35 Sch=hdmi_tx_clk_n
set_property -dict { PACKAGE_PIN L16   IOSTANDARD TMDS_33  } [get_ports { TMDS_clk_p }]; #IO_L11P_T1_SRCC_35 Sch=hdmi_tx_clk_p
set_property -dict { PACKAGE_PIN K18   IOSTANDARD TMDS_33  } [get_ports { TMDS_data_n[0] }]; #IO_L12N_T1_MRCC_35 Sch=hdmi_tx_d_n[0]
set_property -dict { PACKAGE_PIN K17   IOSTANDARD TMDS_33  } [get_ports { TMDS_data_p[0] }]; #IO_L12P_T1_MRCC_35 Sch=hdmi_tx_d_p[0]
set_property -dict { PACKAGE_PIN J19   IOSTANDARD TMDS_33  } [get_ports { TMDS_data_n[1] }]; #IO_L10N_T1_AD11N_35 Sch=hdmi_tx_d_n[1]
set_property -dict { PACKAGE_PIN K19   IOSTANDARD TMDS_33  } [get_ports { TMDS_data_p[1] }]; #IO_L10P_T1_AD11P_35 Sch=hdmi_tx_d_p[1]
set_property -dict { PACKAGE_PIN H18   IOSTANDARD TMDS_33  } [get_ports { TMDS_data_n[2] }]; #IO_L14N_T2_AD4N_SRCC_35 Sch=hdmi_tx_d_n[2]
set_property -dict { PACKAGE_PIN J18   IOSTANDARD TMDS_33  } [get_ports { TMDS_data_p[2] }]; #IO_L14P_T2_AD4P_SRCC_35 Sch=hdmi_tx_d_p[2]
#set_property -dict { PACKAGE_PIN R19   IOSTANDARD LVCMOS33 } [get_ports { hdmi_tx_hpdn }]; #IO_0_34 Sch=hdmi_tx_hpdn
