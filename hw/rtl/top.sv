`timescale 1ns / 1ps

module top(
    inout  wire  [14:0] DDR_addr,
    inout  wire  [2:0]  DDR_ba,
    inout  wire         DDR_cas_n,
    inout  wire         DDR_ck_n,
    inout  wire         DDR_ck_p,
    inout  wire         DDR_cke,
    inout  wire         DDR_cs_n,
    inout  wire  [3:0]  DDR_dm,
    inout  wire  [31:0] DDR_dq,
    inout  wire  [3:0]  DDR_dqs_n,
    inout  wire  [3:0]  DDR_dqs_p,
    inout  wire         DDR_odt,
    inout  wire         DDR_ras_n,
    inout  wire         DDR_reset_n,
    inout  wire         DDR_we_n,

    inout  wire         FIXED_IO_ddr_vrn,
    inout  wire         FIXED_IO_ddr_vrp,
    inout  wire  [53:0] FIXED_IO_mio,
    inout  wire         FIXED_IO_ps_clk,
    inout  wire         FIXED_IO_ps_porb,
    inout  wire         FIXED_IO_ps_srstb,

    input  wire  [3:0]  btns_4bits_tri_i,
    inout  wire  [3:0]  leds_4bits_tri_io,
    inout  wire  [5:0]  rgb_led_tri_io,
    input  wire  [1:0]  sws_2bits_tri_i,

    output wire         TMDS_clk_n,
    output wire         TMDS_clk_p,
    output wire  [2:0]  TMDS_data_n,
    output wire  [2:0]  TMDS_data_p,

    inout  wire         vid_l_iic_scl,
    inout  wire         vid_l_iic_sda,
    input  wire  [7:0]  vid_l_data,
    input  wire         vid_l_hsync,
    input  wire         vid_l_pclk,
    input  wire         vid_l_vsync,
    output wire         vid_l_rst,

    inout  wire         vid_r_iic_scl,
    inout  wire         vid_r_iic_sda,
    input  wire  [7:0]  vid_r_data,
    input  wire         vid_r_hsync,
    input  wire         vid_r_pclk,
    input  wire         vid_r_vsync,
    output wire         vid_r_rst
);

    assign vid_l_rst = 1'b1;
    assign vid_r_rst = 1'b1;

    system_wrapper system(
        .DDR_addr,
        .DDR_ba,
        .DDR_cas_n,
        .DDR_ck_n,
        .DDR_ck_p,
        .DDR_cke,
        .DDR_cs_n,
        .DDR_dm,
        .DDR_dq,
        .DDR_dqs_n,
        .DDR_dqs_p,
        .DDR_odt,
        .DDR_ras_n,
        .DDR_reset_n,
        .DDR_we_n,

        .FIXED_IO_ddr_vrn,
        .FIXED_IO_ddr_vrp,
        .FIXED_IO_mio,
        .FIXED_IO_ps_clk,
        .FIXED_IO_ps_porb,
        .FIXED_IO_ps_srstb,

        .btns_4bits_tri_i,
        .leds_4bits_tri_io,
        .rgb_led_tri_io,
        .sws_2bits_tri_i,

        .TMDS_clk_n,
        .TMDS_clk_p,
        .TMDS_data_n,
        .TMDS_data_p,

        .vid_xclk           (),

        .vid_l_iic_scl_io   (vid_l_iic_scl),
        .vid_l_iic_sda_io   (vid_l_iic_sda),
        .vid_l_data,
        .vid_l_hsync,
        .vid_l_pclk,
        .vid_l_vsync,

        .vid_r_iic_scl_io   (vid_r_iic_scl),
        .vid_r_iic_sda_io   (vid_r_iic_sda),
        .vid_r_data,
        .vid_r_hsync,
        .vid_r_pclk,
        .vid_r_vsync
    );

endmodule
