proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}

set required_version 2018.2

# create variables with absolute folders for all necessary folders
set hw_dir [get_script_folder]
set repo_dir [file normalize $hw_dir/..]
set work_dir [file normalize $repo_dir/work]
set sdk_dir [file normalize $repo_dir/sw]
set hls_dir [file normalize $repo_dir/hls]
set ip_repo_dir [file normalize $repo_dir/ip_repo]
set tmp_dir [file normalize $work_dir/tmp]

set clean "no"
set project "init"
set version_override "no"
set sdk "no"

puts "
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-                                                     -*
*-         Welcome to the Vivado Project Builder       -*
*-       Created by Haozhe Zhu, Inspired by Avnet      -*
*-                                                     -*
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"

set ranonce "false"
set build_params ""
# to adjust the width of the chart, need to adjust this as well as the "predefined"
# chart elements below (there are 4 lines that need to be adjusted)
set chart_wdith 30
# need to add debug printing to a log
for {set i 0} {$i < [llength $argv]} {incr i} {
    if {[string match -nocase "*help*" [lindex $argv $i]]} {
        puts "Parameters are:"
        puts "  - project=<project_name>\n"
        puts "  - sdk="
        puts "        'yes' will attempt to execute: \"./make_sdk.tcl\" to build the "
        puts "        SDK portion of the project."
        puts "  - clean=\n Be careful due to destructive nature of wiping ALL output products out"
        puts "  - version_override=yes"
        puts "***************************** \n CAUTION: \n Override the Version Check\n and attempt to make project\n *****************************"
        return -code ok
    } elseif [string match -nocase "false" $ranonce] {
        set ranonce "true"
        set build_params "\n"
        append build_params "+------------------+------------------------------------+\n"
        append build_params "| Setting          |     Configuration                  |\n"
        append build_params "+------------------+------------------------------------+\n"
    }
    # check for CLEAN parameter
    if {[string match -nocase "clean=*" [lindex $argv $i]]} {
        set clean [string range [lindex $argv $i] 6 end]
        set printmessage $clean
        for {set j 0} {$j < [expr $chart_wdith - [string length $clean]]} {incr j} {
            append printmessage " "
        }
        append build_params "| Clean            |     $printmessage |\n"
    }
    # check for PROJECT parameter
    if {[string match -nocase "project=*" [lindex $argv $i]]} {
        set project [string range [lindex $argv $i] 8 end]
        set printmessage $project
        for {set j 0} {$j < [expr $chart_wdith - [string length $project]]} {incr j} {
            append printmessage " "
        }
        append build_params "| Project          |     $printmessage |\n"
    }
    # check for SDK parameter
    if {[string match -nocase "sdk=*" [lindex $argv $i]]} {
        set sdk [string range [lindex $argv $i] 4 end]
        set printmessage $sdk
        for {set j 0} {$j < [expr $chart_wdith - [string length $sdk]]} {incr j} {
            append printmessage " "
        }
        append build_params "| SDK              |     $printmessage |\n"
    }
    # check for Version parameter
    if {[string match -nocase "version_override=*" [lindex $argv $i]]} {
        set version_override [string range [lindex $argv $i] 17 end]
        set printmessage $version_override
        for {set j 0} {$j < [expr $chart_wdith - [string length $version_override]]} {incr j} {
            append printmessage " "
        }
        append build_params "| Version override |     $printmessage |\n"
    }
    append build_params "+------------------+------------------------------------+\n"
}
append build_params "\n\n"
puts $build_params
unset printmessage
unset ranonce

# Clean the output files
if {[string match -nocase "yes" $clean]} {
    puts "*WARN*  Cleaning the whole working folder..."
    if {[file exists $work_dir] == 1} {
        file delete -force -- $work_dir
    }
    return -code ok
}

#version check
set version [version -short]
if {[string match -nocase "yes" $version_override]} {
    puts "*WARN*  Version check skip. Please check the design for validity."
} else {
    if { [string first $required_version $version] == -1 } {
        puts "*ERROR* Version $version of Vivado not acceptable. Please run with Vivado $required_version to continue."
        return -code ok
    } else {
        puts "*INFO*  Version of Vivado acceptable, continuing..."
    }
}

# If variables do not exist, exit script
if {[string match -nocase "init" $project]} {
    puts "*ERROR* Project name undefined. please check and try again."
    return -code ok
}

set proj_name "${project}"

if {[file exists $work_dir] == 0} {
    puts "*INFO*  Folder \"work\" does NOT exist. Create a new one."
    file mkdir $work_dir
}

if {[file exists $tmp_dir] == 0} {
    puts "*INFO*  Folder \"tmp\" does NOT exist. Create a new one."
    file mkdir $tmp_dir
}

if {[file isfile $hw_dir/script/create_proj.tcl]} {
    puts "*INFO*  Setting up project \"$proj_name\"..."
    source $hw_dir/script/create_proj.tcl -notrace
} else {
    puts "*ERROR* Project script does NOT exist. Check it and try Again."
    return -code ok
}

# attempt to build SDK portion
set sdk_path_tcl $tmp_dir/sdk_path.tcl
if {[file exists $sdk_path_tcl] == 1} {
    puts "*WARN*  \"sdk_path.tcl\" has existed. Prepare to overwrite."
}
set fp_sdk_path [open $sdk_path_tcl w]
puts $fp_sdk_path "set proj_name $proj_name"
puts $fp_sdk_path "set proj_dir $work_dir/$proj_name"
close $fp_sdk_path
unset fp_sdk_path
unset sdk_path_tcl

if {[string match -nocase "yes" $sdk]} {
    puts "*INFO*  Attempting to build SDK..."
    if {[file isfile $hw_dir/script/create_sdk.tcl]} {
        puts "*INFO*  Setting up SDK sub-project \"$proj_name\"..."
        exec xsdk -batch -source $hw_dir/script/create_sdk.tcl -notrace
    } else {
        puts "*ERROR* SDK sub-project script does NOT exist. Check it and try Again."
        return -code ok
    }
    puts "*INFO*  Launching SDK GUI..."
    launch_sdk -workspace "$proj_dir/${proj_name}.sdk" \
               -hwspec "$proj_dir/${proj_name}.sdk/top.hdf"
}
