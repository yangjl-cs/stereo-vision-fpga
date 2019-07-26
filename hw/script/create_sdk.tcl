proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}

puts "*INFO*  Running script \"create_sdk.tcl\"."

set hw_name "top_hw_platform_0"
set bsp_name "stereovision_bsp"
set app_name "stereovision"

set hw_dir [file normalize "[get_script_folder]/.."]
set repo_dir [file normalize "$hw_dir/.."]
set work_dir "$repo_dir/work"

# Import $proj_name & $proj_dir
source "$work_dir/tmp/sdk_path.tcl"

set sdk_dir "$proj_dir/${proj_name}.sdk"
if {[file exists $sdk_dir] == 1} {
    puts "*WARN*  Folder \"$sdk_dir\" has existed. Prepare to Overwrite."
    file delete -force -- $sdk_dir
}
file mkdir $sdk_dir

# ==============================================================================
#   Set workspace and import hardware platform

setws $sdk_dir

puts "*INFO*  Adding local user repository."
repo -set $repo_dir/ip_repo

puts "*INFO*  Import hardware definition from impl_1 folder."
file copy -force $proj_dir/${proj_name}.runs/impl_1/top.sysdef $sdk_dir/top.hdf
createhw -name $hw_name -hwspec $sdk_dir/top.hdf

# ==============================================================================
#   Generate BSP

puts "*INFO*  Creating BSP \"$bsp_name\"."
createbsp -name ${bsp_name} -proc ps7_cortexa9_0 -hwproject ${hw_name} -os standalone

# add libraries for APP
setlib -bsp ${bsp_name} -lib xilffs

# regen and build
regenbsp -hw ${hw_name} -bsp ${bsp_name}
projects -build -type bsp -name ${bsp_name}

# ==============================================================================
#   Create APP
puts "*INFO*  Creating application \"$app_name\"."
createapp -name ${app_name} \
          -hwproject ${hw_name} \
          -proc ps7_cortexa9_0 \
          -os standalone \
          -lang C++ \
          -app {Empty Application} \
          -bsp ${bsp_name}

# remove default main() function
exec rm $sdk_dir/$app_name/src/main.cc

# copy sources to empty application
importsources -name ${app_name} -path $repo_dir/sw

# build APP
puts "*INFO*  Build ${app_name}."
configapp -app ${app_name} -add compiler-misc {-Ixilffs}
projects -build -type app -name ${app_name}

puts "*INFO*  Exit from \"create_sdk.tcl\" and return to \"create_proj.tcl\"."
