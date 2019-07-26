puts "*INFO*  Running script \"create_proj.tcl\"."

# Create Vivado project
puts "*INFO*  Creating Vivado Project..."
create_project $proj_name "$work_dir/$proj_name"

# Set the directory path for the new project
set proj_dir [get_property directory [current_project]]

# Set project properties
set_property "default_lib" "xil_defaultlib" [current_project]
set_property "part" "xc7z020clg400-1" [current_project]
set_property "board_part" "tul.com.tw:pynq-z2:part0:1.0" [current_project]
set_property "simulator_language" "Mixed" [current_project]
set_property "target_language" "Verilog" [current_project]

# Import third-part IP files
set_property ip_repo_paths $ip_repo_dir [current_project]
update_ip_catalog

# ==============================================================================
#  Source Files

puts "*INFO*  Adding source files."

# Create 'sources_1' fileset (if not found)
if {[string equal [get_filesets -quiet sources_1] ""]} {
  create_fileset -srcset sources_1
}

# Add RTL files
add_files -fileset sources_1 "$hw_dir/rtl"

# Set 'sources_1' fileset properties
set_property -name "top" -value "top" -objects [get_filesets sources_1]

# ==============================================================================
#   Block Design Files

puts "*INFO*  Creating block design."

source "$hw_dir/script/create_bd.tcl"

regenerate_bd_layout

make_wrapper -files [get_files system.bd] -top
add_files -fileset sources_1 "$proj_dir/$proj_name.srcs/sources_1/bd/system/hdl/system_wrapper.v"

puts "*INFO*  Block design created: \"system.bd\"."

# ==============================================================================
#   Constraint Files

puts "*INFO*  Adding constraint files."

# Create 'constrs_1' fileset (if not found)
if {[string equal [get_filesets -quiet constrs_1] ""]} {
  create_fileset -constrset constrs_1
}

add_files -fileset constrs_1 "$hw_dir/xdc"

# ==============================================================================
#   Simulation Files

puts "*INFO*  Adding simulation testbench files."

# Create 'sim_1' fileset (if not found)
if {[string equal [get_filesets -quiet sim_1] ""]} {
  create_fileset -simset sim_1
}

# Set 'sim_1' fileset properties
set_property -name "verilog_define" -value "SIMULATION" -objects [get_filesets sim_1]
set_property -name {xsim.simulate.log_all_signals} -value {true} -objects [get_filesets sim_1]

puts "*WARN*  No simulation files found. Skipped."

update_compile_order -fileset sources_1
update_compile_order -fileset sim_1

puts "*INFO*  Start synthesis & implementation, which may takes much time."
launch_runs impl_1 -to_step write_bitstream -j 8
wait_on_run impl_1 -quiet

puts "*INFO*  Projected created: \"$proj_name\"."
puts "*INFO*  Exit from \"create_proj.tcl\" and return to \"make.tcl\"."
