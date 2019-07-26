proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}

set proj_name sv_hls
set hls_dir [get_script_folder]
set repo_dir [file normalize $hls_dir/..]
set work_dir [file normalize $repo_dir/work]
set proj_dir [file normalize $work_dir/$proj_name]

cd $work_dir
open_project -reset $proj_name
set_top stereo_vision
add_files $hls_dir/src/stereovision.cc -cflags "-Iinclude"
add_files $hls_dir/src/stereovision.h
add_files $hls_dir/src/camera_param.h

add_files -tb $hls_dir/src/tb_stereovision.cc -cflags "-Iinclude"

open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
set_clock_uncertainty 27.0%

csynth_design
export_design -format ip_catalog -display_name "Stereo Vision"
exit
