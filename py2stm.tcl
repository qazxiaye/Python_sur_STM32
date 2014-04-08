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
    colorShow "         RICM Project : Python sur STM32        " green
    puts "-------------------------------------------------"

	colorShow "Usage:" yellow 1
	puts -nonewline " $pname "
	colorShow "\[-d\] \[-b\]" blue 1
	colorShow "-p" blue 1
	puts " py_file "
	showInfo "\[-d\]" blue " : Debug Mode, will surpport printf in the project."
	showInfo "\[-b\]" blue " : Burn  Mode, will burn the program on the card when finish compile."
	puts ""

    showInfo "Example:" yellow " $pname -d -p /home/share/test.py"
    puts ""
}

#-------------------------check parameter----------------------------------------
if {$argc<2 || $argc>4} {
    Usage
    exit 0
}

set cnt 0
set DEBUG 0
set ToBurn 0
set p_arg ""
while {$cnt < $argc} {
	set arg [lindex $argv $cnt]
	switch -- $arg {
		-b {
			set ToBurn 1
			incr cnt
		}
		-d {
			set DEBUG 1
			incr cnt
		}
		-p {
			incr cnt
			set p_arg [lindex $argv $cnt]
			incr cnt
		}
		default {
			colorShow "Error:" red 1
			puts -nonewline " Unknown argument: "
			colorShow $arg red
			puts ""
			Usage
			exit 1
		}
	}
}

set path_str_index [string last "/" [lindex $p_arg 0]]
set PY_FILE_PATH [string range [lindex $p_arg 0] 0 $path_str_index]
set PY_FILE_NAME [string range [lindex $p_arg 0] [expr $path_str_index+1] end]
set FILE_NAME [string range $PY_FILE_NAME 0 [expr [string length $PY_FILE_NAME]-4]]

cd $PY_FILE_PATH

#-------------------------call shedskin------------------------------------
colorShow "Translating..." yellow
catch {
	exec shedskin $PY_FILE_NAME
} msg

if {[string first "ERROR" $msg] > -1} {
	colorShow $msg red
	exit 0
}
puts $msg

#-----------------------cpp-----------------------------------------------------
colorShow "Treating Source Files..." yellow
set DirName stm_$FILE_NAME
file mkdir $DirName

#set cpp_contenu [exec cat ./${FILE_NAME}.cpp | sed "s/__ss_int/int/g" | sed "s/str/std::string/g" | sed "s/#include \"builtin.hpp\"/#include \"config\\/stm32plus.h\"\\n#include \"config\\/net.h\"/g" | sed "s/__shedskin__::__init();//g"]
#set i [string first "__shedskin__::__start" $cpp_contenu]
#set j [string first ";" $cpp_contenu $i]
#set str [string range $cpp_contenu $i $j]
#set cpp_contenu [string replace $cpp_contenu $i $j [string range $str 22 [expr [string length $str]-3]]()\;]










if {$DEBUG == 1} {
	set cpp_contenu [exec cat ./${FILE_NAME}.cpp | \
	sed "s/#include \"$FILE_NAME.hpp\"/#include \"$FILE_NAME.hpp\"\\nextern \"C\" \{\\n#include \"stm32f4xx.h\" \\n#include \"stm32f4_discovery.h\" \\n#include <stdio.h> \\n#include \"stm32f4xx_conf.h\" \\n#include \"stm32f4xx.h\" \\n#include \"usbd_cdc_core.h\"\\n#include \"usbd_usr.h\"\\n#include \"usbd_desc.h\"\\n#include \"usbd_cdc_vcp.h\"\\n\\n__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;\\n\}/g" | \
	sed "s/int main(int, char \\*\\*) \{/int main(int, char \\*\\*) \{\\n\\n    USBD_Init(\\&USB_OTG_dev, USB_OTG_FS_CORE_ID, \\&USR_desc, \\&USBD_CDC_cb, \\&USR_cb);\\n    setbuf(stdout, NULL);/g"]
} else {
	set cpp_contenu [exec cat ./${FILE_NAME}.cpp]
}

#

#-----------------------hpp-----------------------------------------------------
#set hpp_contenu [exec cat ./${FILE_NAME}.hpp | sed "s/using namespace __shedskin__;//g" | sed "s/__ss_int/int/g" | sed "s/str/std::string/g"]
set hpp_contenu [exec cat ./${FILE_NAME}.hpp]

#---------------------------debug print------------------------------------------
if {$DEBUG == 1} {
	if {[file exists ${PY2STM_PATH}/print/test.bin] == 0} {
		colorShow "Print Preparing..." yellow
		cd ${PY2STM_PATH}/print
		set m_index [open Makefile w]

		set contenu "STLINK=$STLINK_PATH
CC=${GCC_PATH}/arm-none-eabi-gcc
CPP=${GCC_PATH}/arm-none-eabi-g++
OBJCOPY=${GCC_PATH}/arm-none-eabi-objcopy
"
		append contenu [exec cat Makefile_print]
		puts $m_index $contenu
		close $m_index

		catch {[exec make]} msg

        puts $msg
		cd ${PY2STM_PATH}/$PY_FILE_PATH
	}
}

#-----------------------Makefile-----------------------------------------------------
set makefile_contenu "PRO_NAME=$FILE_NAME

GCC_PATH=$GCC_PATH
STLINK=$STLINK_PATH
STM32PLUS_LIB=$STM32PLUS_LIB_PATH
SHEDSKIN_LIB=${PY2STM_PATH}/shedskin_lib
"

if {$DEBUG == 1} {
	set makefile_contenu "$makefile_contenu
STM_COMMON_LIB=${PY2STM_PATH}/print
"
}

set makefile_contenu "$makefile_contenu
BUILD_PATH=.

CCFLAGS=-c -pedantic-errors -fno-rtti -std=gnu++0x -fno-threadsafe-statics -pipe -ffunction-sections -fdata-sections -fno-exceptions -mthumb -gdwarf-2 -pipe -DHSE_VALUE=8000000 -mcpu=cortex-m4 -DSTM32PLUS_F4 -Os
STM32PLUS_I_FLAG=-I\${STM32PLUS_LIB}/include -I\${STM32PLUS_LIB}/include/stl -I\${STM32PLUS_LIB} -I\${BUILD_PATH}
SHEDSKIN_I_FLAG=-I\${SHEDSKIN_LIB} -I\${SHEDSKIN_LIB}/builtin
"

if {$DEBUG == 1} {
	set makefile_contenu "$makefile_contenu
PRINT_I_FLAG  = -I\$(STM_COMMON_LIB)/Utilities/STM32F4-Discovery
PRINT_I_FLAG += -I\$(STM_COMMON_LIB)/Libraries/CMSIS/Include 
PRINT_I_FLAG += -I\$(STM_COMMON_LIB)/Libraries/CMSIS/ST/STM32F4xx/Include
PRINT_I_FLAG += -I\$(STM_COMMON_LIB)/Libraries/STM32F4xx_StdPeriph_Driver/inc
PRINT_I_FLAG += -I\$(STM_COMMON_LIB)/Libraries/STM32_USB_Device_Library/Class/cdc/inc
PRINT_I_FLAG += -I\$(STM_COMMON_LIB)/Libraries/STM32_USB_Device_Library/Core/inc
PRINT_I_FLAG += -I\$(STM_COMMON_LIB)/Libraries/STM32_USB_OTG_Driver/inc
PRINT_I_FLAG += -I\$(STM_COMMON_LIB)
"
}

set makefile_contenu "$makefile_contenu
all:
"

set m_cpp_files [exec cat Makefile | grep cpp | grep SHEDSKIN_LIBDIR]
set o_file_names ""
foreach m_cpp_file $m_cpp_files {
	set cpp_file_name [string range $m_cpp_file [expr [string last "/" $m_cpp_file]+1] end]
	set file_name [string range $cpp_file_name 0 [expr [string length $cpp_file_name]-5]]
	set makefile_contenu "$makefile_contenu
	\${GCC_PATH}/arm-none-eabi-g++ -o \${BUILD_PATH}/${file_name}.o \${CCFLAGS} \${STM32PLUS_I_FLAG} \${SHEDSKIN_I_FLAG} \${SHEDSKIN_LIB}/$cpp_file_name"
	set o_file_names "$o_file_names ${file_name}.o"
}


if {$DEBUG == 1} {
	set makefile_contenu "$makefile_contenu
	\${GCC_PATH}/arm-none-eabi-g++ -o \${BUILD_PATH}/${FILE_NAME}.o \${CCFLAGS} \${STM32PLUS_I_FLAG} \${SHEDSKIN_I_FLAG} \${PRINT_I_FLAG} \${BUILD_PATH}/${FILE_NAME}.cpp"
} else {
	set makefile_contenu "$makefile_contenu
	\${GCC_PATH}/arm-none-eabi-g++ -o \${BUILD_PATH}/${FILE_NAME}.o \${CCFLAGS} \${STM32PLUS_I_FLAG} \${SHEDSKIN_I_FLAG} \${BUILD_PATH}/${FILE_NAME}.cpp"
}

set makefile_contenu "$makefile_contenu
	\${GCC_PATH}/arm-none-eabi-g++ -o LibraryHacks.o \${CCFLAGS} \${STM32PLUS_I_FLAG} \${BUILD_PATH}/LibraryHacks.cpp  
	\${GCC_PATH}/arm-none-eabi-gcc -o System.o -c -ffunction-sections -fdata-sections -fno-exceptions -mthumb -gdwarf-2 -pipe -DHSE_VALUE=8000000 -mcpu=cortex-m4 -DSTM32PLUS_F4 -Os \${STM32PLUS_I_FLAG} \${BUILD_PATH}/System.c
	\${GCC_PATH}/arm-none-eabi-as -mcpu=cortex-m4 -I\${BUILD_PATH} -o Startup.o Startup.asm"

if {$DEBUG == 1} {
	set makefile_contenu "$makefile_contenu
	\${GCC_PATH}/arm-none-eabi-g++ -o \${BUILD_PATH}/\${PRO_NAME}.elf -Xlinker --gc-sections -mthumb -g3 -gdwarf-2 -mcpu=cortex-m4 -Wl,-wrap,__aeabi_unwind_cpp_pr0 -Wl,-wrap,__aeabi_unwind_cpp_pr1 -Wl,-wrap,__aeabi_unwind_cpp_pr2 -Tstm32_flash.ld ${o_file_names} LibraryHacks.o Startup.o System.o \${PRO_NAME}.o \${STM32PLUS_LIB}/build/small-f4-8000000/libstm32plus-master-f4-small.a ${PY2STM_PATH}/print/stm32f4xx_rcc.o ${PY2STM_PATH}/print/stm32f4xx_gpio.o ${PY2STM_PATH}/print/stm32f4xx_syscfg.o ${PY2STM_PATH}/print/stm32f4xx_exti.o ${PY2STM_PATH}/print/misc.o ${PY2STM_PATH}/print/syscalls.o ${PY2STM_PATH}/print/usbd_cdc_vcp.o ${PY2STM_PATH}/print/usbd_usr.o ${PY2STM_PATH}/print/usbd_desc.o ${PY2STM_PATH}/print/usb_bsp.o ${PY2STM_PATH}/print/usbd_cdc_core.o ${PY2STM_PATH}/print/usb_dcd.o ${PY2STM_PATH}/print/usbd_ioreq.o ${PY2STM_PATH}/print/usbd_req.o ${PY2STM_PATH}/print/usb_core.o ${PY2STM_PATH}/print/usbd_core.o ${PY2STM_PATH}/print/usb_dcd_int.o  ${PY2STM_PATH}/print/stm32f4xx_it.o ${PY2STM_PATH}/print/stm32f4_discovery.o"
} else {
	set makefile_contenu "$makefile_contenu
	\${GCC_PATH}/arm-none-eabi-g++ -o \${BUILD_PATH}/\${PRO_NAME}.elf -Xlinker --gc-sections -mthumb -g3 -gdwarf-2 -mcpu=cortex-m4 -Wl,-wrap,__aeabi_unwind_cpp_pr0 -Wl,-wrap,__aeabi_unwind_cpp_pr1 -Wl,-wrap,__aeabi_unwind_cpp_pr2 -Tstm32_flash.ld ${o_file_names} LibraryHacks.o Startup.o System.o \${PRO_NAME}.o \${STM32PLUS_LIB}/build/small-f4-8000000/libstm32plus-master-f4-small.a"
}
set makefile_contenu "$makefile_contenu
	\${GCC_PATH}/arm-none-eabi-objcopy -O binary \${BUILD_PATH}/\${PRO_NAME}.elf \${BUILD_PATH}/\${PRO_NAME}.bin

clean:
	rm -f *.o *.bin *.elf

burn:
	\$(STLINK)/st-flash write \$(PRO_NAME).bin 0x8000000
"

#-----------------------Write file-----------------------------------------------------
colorShow "New Project Creating..." yellow
file copy -force ${PY2STM_PATH}/stm32_flash.ld   $DirName
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
puts $make_index $makefile_contenu
close $make_index


set is_exception ""
catch {set is_exception [exec grep -w catch ./${FILE_NAME}.cpp]} msg
if {$is_exception eq ""} {
	catch {set is_exception [exec grep -w throw ./${FILE_NAME}.cpp]} msg
}
if {$is_exception eq ""} {
	catch {set is_exception [exec grep -w ASSERT ./${FILE_NAME}.cpp]} msg
}

if {$is_exception ne ""} {
	set f_new_cpp [open ./${FILE_NAME}.cpp.tmp w]
	set f_cpp [open ./${FILE_NAME}.cpp r]
	while {![eof $f_cpp]} {
		gets $f_cpp line
		set pos_catch [string first "catch" $line]

		if {$pos_catch!=-1} {
			set index -1
			set pos [expr $pos_catch - 2]

			while {$index ne $pos} {
				gets $f_cpp line
				set index [string first \175 $line]
			}
		} elseif {[string first "try" $line]==-1 && [string first "throw" $line]==-1  && [string first "ASSERT" $line]==-1} {
			puts $f_new_cpp $line
		} else {
			puts $f_new_cpp ";"
		}
	}

	close $f_cpp
	close $f_new_cpp
	file rename -force ./${FILE_NAME}.cpp.tmp ./${FILE_NAME}.cpp
}

set is_print2 ""
catch {set is_print2 [exec grep -w print2 ./${FILE_NAME}.cpp]} msg
if {$is_print2 ne ""} {
	set f_new_cpp [open ./${FILE_NAME}.cpp.tmp w]
	set f_cpp [open ./${FILE_NAME}.cpp r]
	while {![eof $f_cpp]} {
		gets $f_cpp line
		set pos_catch [string first "catch" $line]

		if {[string first "print2" $line]==-1} {
			puts $f_new_cpp $line
		} else {
			puts $f_new_cpp ";"
		}
	}

	close $f_cpp
	close $f_new_cpp
	file rename -force ./${FILE_NAME}.cpp.tmp ./${FILE_NAME}.cpp
}

#-----------------------make and execute-----------------------------------------------------
colorShow "Compiling..." yellow
catch {exec make} msg
puts ""
puts ""
puts $msg

if {$ToBurn == 1} {
    colorShow "Burning..." yellow
    puts ""
    puts ""
    catch {exec make burn} msg
    if {[string first "ERROR" $msg] > -1} {
    	showInfo "Error:" red "Cannot connect with the card. 
    	We suggest you to run st-util clicking the reset button before you run this program!"
    	exit 0
    }
    puts $msg
}

