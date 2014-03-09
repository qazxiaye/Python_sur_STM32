#!/bin/sh
# The backslash makes the next line a comment in Tcl \
exec tclsh "$0" ${1+"$@"}

#--------------------------------------------------------------------------------
set GCC_PATH "~/lib/gcc-arm-none-eabi-4_7-2013q2/bin"
set STM32PLUS_LIB_PATH "/home/xavier/project/stm32/stm32plus/lib"
set STLINK_PATH "/home/xavier/lib/stlink"
set PY2STM_PATH [pwd]

#--------------------------------------------------------------------------------
proc colorShow {str fg {nonewline 0}} {
        set fgList "30 black 31 red 32 green 33 yellow 34 blue 37 white"
        set fgNo   [lindex $fgList [expr [lsearch $fgList $fg] - 1]]
        set str    "\033\[;${fgNo}m$str\033\[0m"
		if {$nonewline != 1} {
			puts "$str"
		} else {
			puts -nonewline "$str"
		}
}


#--------------------------------------------------------------------------------
proc showInfo {args} {
	foreach {title col str} $args {
		colorShow $title $col 1
		puts $str
	}
}


#--------------------------------------------------------------------------------
proc Usage {} {
    global argv0
    set pname [file tail $argv0]

    puts "-------------------------------------------------"
    puts "         RICM Project : Python sur STM32        "
    puts "-------------------------------------------------"
    showInfo "Usage:" yellow " $pname py_File"
    showInfo "Example:" yellow " $pname /home/share/test.py"
    puts ""
}

#--------------------------------------------------------------------------------
proc cppReplace {contenu} {
	set new_contenu [string replace ]
}

#--------------------------------------------------------------------------------
proc hppReplace {contenu} {

}

#-------------------------check parameter----------------------------------------
if {$argc != 1} {
    Usage
    exit 0
}

set path_str_index [string last "/" [lindex $argv 0]]
set PY_FILE_PATH [string range [lindex $argv 0] 0 $path_str_index]
set PY_FILE_NAME [string range [lindex $argv 0] [expr $path_str_index+1] end]
set FILE_NAME [string range $PY_FILE_NAME 0 [expr [string length $PY_FILE_NAME]-4]]

cd $PY_FILE_PATH

#-------------------------call shedskin------------------------------------
catch {
	exec shedskin $PY_FILE_NAME
} msg

if {[string first "ERROR" $msg] > -1} {
	colorShow $msg red
	exit 0
}
puts $msg

#-----------------------cpp-----------------------------------------------------
set DirName stm_$FILE_NAME
file mkdir $DirName

set cpp_contenu [exec cat ./${FILE_NAME}.cpp | sed "s/__ss_int/int/g" | sed "s/str/std::string/g" | sed "s/#include \"builtin.hpp\"/#include \"config\\/stm32plus.h\"\\n#include \"config\\/net.h\"/g" | sed "s/__shedskin__::__init();//g"]
set i [string first "__shedskin__::__start" $cpp_contenu]
set j [string first ";" $cpp_contenu $i]
set str [string range $cpp_contenu $i $j]
set cpp_contenu [string replace $cpp_contenu $i $j [string range $str 22 [expr [string length $str]-3]]()\;]

#-----------------------hpp-----------------------------------------------------
set hpp_contenu [exec cat ./${FILE_NAME}.hpp | sed "s/using namespace __shedskin__;//g" | sed "s/__ss_int/int/g" | sed "s/str/std::string/g"]

#-----------------------Makefile-----------------------------------------------------
set basic_makefile_contenu "PRO_NAME=$FILE_NAME

GCC_PATH=$GCC_PATH
LIB_PATH=$STM32PLUS_LIB_PATH
STLINK=$STLINK_PATH

CPPFILES=\${PRO_NAME}.cpp
HPPFILES=\${PRO_NAME}.hpp

BUILD_PATH=.


.PHONY: all clean


all:	\${PRO_NAME}

\${PRO_NAME}:	\$(CPPFILES) \$(HPPFILES)
	\${GCC_PATH}/arm-none-eabi-g++ -o \${BUILD_PATH}/\${PRO_NAME}.o -c -pedantic-errors -fno-rtti -std=gnu++0x -fno-threadsafe-statics -pipe -Wall -Werror -ffunction-sections -fdata-sections -fno-exceptions -mthumb -gdwarf-2 -pipe -DHSE_VALUE=8000000 -mcpu=cortex-m4 -DSTM32PLUS_F4 -Os -I\${LIB_PATH}/include -I\${LIB_PATH}/include/stl -I$\{LIB_PATH} -I\${BUILD_PATH} \${CPPFILES}
	\${GCC_PATH}/arm-none-eabi-g++ -o LibraryHacks.o -c -Wextra -Werror -pedantic-errors -fno-rtti -std=gnu++0x -fno-threadsafe-statics -pipe -Wall -Werror -ffunction-sections -fdata-sections -fno-exceptions -mthumb -gdwarf-2 -pipe -DHSE_VALUE=8000000 -mcpu=cortex-m4 -DSTM32PLUS_F4 -Os -I\${LIB_PATH}/include -I\${LIB_PATH}/include/stl -I\${LIB_PATH} -I\${BUILD_PATH} \${BUILD_PATH}/LibraryHacks.cpp
	\${GCC_PATH}/arm-none-eabi-as -mcpu=cortex-m4 -I\${BUILD_PATH} -o Startup.o Startup.asm
	\${GCC_PATH}/arm-none-eabi-gcc -o System.o -c -Wall -Werror -ffunction-sections -fdata-sections -fno-exceptions -mthumb -gdwarf-2 -pipe -DHSE_VALUE=8000000 -mcpu=cortex-m4 -DSTM32PLUS_F4 -Os -I\${LIB_PATH}/include -I\${LIB_PATH}/include/stl -I\${LIB_PATH} -I\${BUILD_PATH} \${BUILD_PATH}/System.c
	\${GCC_PATH}/arm-none-eabi-g++ -o \${BUILD_PATH}/\${PRO_NAME}.elf -Xlinker --gc-sections -mthumb -g3 -gdwarf-2 -mcpu=cortex-m4 -T\${BUILD_PATH}/Linker.ld -Wl,-wrap,__aeabi_unwind_cpp_pr0 -Wl,-wrap,__aeabi_unwind_cpp_pr1 -Wl,-wrap,__aeabi_unwind_cpp_pr2 \${PRO_NAME}.o LibraryHacks.o Startup.o System.o \${LIB_PATH}/build/small-f4-8000000/libstm32plus-master-f4-small.a
	\${GCC_PATH}/arm-none-eabi-objcopy -O binary \${BUILD_PATH}/\${PRO_NAME}.elf \${BUILD_PATH}/\${PRO_NAME}.bin

clean:
	rm -f *.o \$(PRO_NAME).elf \$(PRO_NAME).hex \$(PRO_NAME).bin

burn:
	\$(STLINK)/st-flash write \$(PRO_NAME).bin 0x8000000
"
#-----------------------Write file-----------------------------------------------------

file copy -force ${PY2STM_PATH}/Linker.ld        $DirName
file copy -force ${PY2STM_PATH}/py2stm.tcl       $DirName
file copy -force ${PY2STM_PATH}/Startup.asm      $DirName
file copy -force ${PY2STM_PATH}/System.c         $DirName
file copy -force ${PY2STM_PATH}/LibraryHacks.cpp $DirName
      
cd $DirName

set cpp_index [open ${FILE_NAME}.cpp w]
puts $cpp_index $cpp_contenu
close $cpp_index

set hpp_index [open ${FILE_NAME}.hpp w]
puts $hpp_index $hpp_contenu
close $hpp_index

set make_index [open Makefile w]
puts $make_index $basic_makefile_contenu
close $make_index



#-----------------------make and execute-----------------------------------------------------
catch {exec make} msg
puts ""
puts ""
puts $msg


puts ""
puts ""
catch {exec make burn} msg
if {[string first "ERROR" $msg] > -1} {
	showInfo "Error:" red "Cannot connect with the card. 
	We suggest you to run st-util clicking the reset button before you run this program!"
	exit 0
}
puts $msg
