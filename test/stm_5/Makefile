PRO_NAME=5

GCC_PATH=~/lib/gcc-arm-none-eabi-4_7-2013q2/bin
STLINK=/home/xavier/lib/stlink
STM32PLUS_LIB=/home/xavier/project/stm32/stm32plus/lib
SHEDSKIN_LIB=/home/xavier/ricm/mul_projet/py2stm/shedskin_lib

STM_COMMON_LIB=/home/xavier/ricm/mul_projet/py2stm/print

BUILD_PATH=.

CCFLAGS=-c -pedantic-errors -fno-rtti -std=gnu++0x -fno-threadsafe-statics -pipe -ffunction-sections -fdata-sections -fno-exceptions -mthumb -gdwarf-2 -pipe -DHSE_VALUE=8000000 -mcpu=cortex-m4 -DSTM32PLUS_F4 -Os
STM32PLUS_I_FLAG=-I${STM32PLUS_LIB}/include -I${STM32PLUS_LIB}/include/stl -I${STM32PLUS_LIB} -I${BUILD_PATH}
SHEDSKIN_I_FLAG=-I${SHEDSKIN_LIB} -I${SHEDSKIN_LIB}/builtin

PRINT_I_FLAG  = -I$(STM_COMMON_LIB)/Utilities/STM32F4-Discovery
PRINT_I_FLAG += -I$(STM_COMMON_LIB)/Libraries/CMSIS/Include 
PRINT_I_FLAG += -I$(STM_COMMON_LIB)/Libraries/CMSIS/ST/STM32F4xx/Include
PRINT_I_FLAG += -I$(STM_COMMON_LIB)/Libraries/STM32F4xx_StdPeriph_Driver/inc
PRINT_I_FLAG += -I$(STM_COMMON_LIB)/Libraries/STM32_USB_Device_Library/Class/cdc/inc
PRINT_I_FLAG += -I$(STM_COMMON_LIB)/Libraries/STM32_USB_Device_Library/Core/inc
PRINT_I_FLAG += -I$(STM_COMMON_LIB)/Libraries/STM32_USB_OTG_Driver/inc
PRINT_I_FLAG += -I$(STM_COMMON_LIB)

all:

	${GCC_PATH}/arm-none-eabi-g++ -o ${BUILD_PATH}/re.o ${CCFLAGS} ${STM32PLUS_I_FLAG} ${SHEDSKIN_I_FLAG} ${SHEDSKIN_LIB}/re.cpp
	${GCC_PATH}/arm-none-eabi-g++ -o ${BUILD_PATH}/builtin.o ${CCFLAGS} ${STM32PLUS_I_FLAG} ${SHEDSKIN_I_FLAG} ${SHEDSKIN_LIB}/builtin.cpp
	${GCC_PATH}/arm-none-eabi-g++ -o ${BUILD_PATH}/5.o ${CCFLAGS} ${STM32PLUS_I_FLAG} ${SHEDSKIN_I_FLAG} ${PRINT_I_FLAG} ${BUILD_PATH}/5.cpp
	${GCC_PATH}/arm-none-eabi-g++ -o LibraryHacks.o ${CCFLAGS} ${STM32PLUS_I_FLAG} ${BUILD_PATH}/LibraryHacks.cpp  
	${GCC_PATH}/arm-none-eabi-gcc -o System.o -c -ffunction-sections -fdata-sections -fno-exceptions -mthumb -gdwarf-2 -pipe -DHSE_VALUE=8000000 -mcpu=cortex-m4 -DSTM32PLUS_F4 -Os ${STM32PLUS_I_FLAG} ${BUILD_PATH}/System.c
	${GCC_PATH}/arm-none-eabi-as -mcpu=cortex-m4 -I${BUILD_PATH} -o Startup.o Startup.asm
	${GCC_PATH}/arm-none-eabi-g++ -o ${BUILD_PATH}/${PRO_NAME}.elf -Xlinker --gc-sections -mthumb -g3 -gdwarf-2 -mcpu=cortex-m4 -Wl,-wrap,__aeabi_unwind_cpp_pr0 -Wl,-wrap,__aeabi_unwind_cpp_pr1 -Wl,-wrap,__aeabi_unwind_cpp_pr2 -Tstm32_flash.ld  re.o builtin.o LibraryHacks.o Startup.o System.o ${PRO_NAME}.o ${STM32PLUS_LIB}/build/small-f4-8000000/libstm32plus-master-f4-small.a /home/xavier/ricm/mul_projet/py2stm/print/stm32f4xx_rcc.o /home/xavier/ricm/mul_projet/py2stm/print/stm32f4xx_gpio.o /home/xavier/ricm/mul_projet/py2stm/print/stm32f4xx_syscfg.o /home/xavier/ricm/mul_projet/py2stm/print/stm32f4xx_exti.o /home/xavier/ricm/mul_projet/py2stm/print/misc.o /home/xavier/ricm/mul_projet/py2stm/print/syscalls.o /home/xavier/ricm/mul_projet/py2stm/print/usbd_cdc_vcp.o /home/xavier/ricm/mul_projet/py2stm/print/usbd_usr.o /home/xavier/ricm/mul_projet/py2stm/print/usbd_desc.o /home/xavier/ricm/mul_projet/py2stm/print/usb_bsp.o /home/xavier/ricm/mul_projet/py2stm/print/usbd_cdc_core.o /home/xavier/ricm/mul_projet/py2stm/print/usb_dcd.o /home/xavier/ricm/mul_projet/py2stm/print/usbd_ioreq.o /home/xavier/ricm/mul_projet/py2stm/print/usbd_req.o /home/xavier/ricm/mul_projet/py2stm/print/usb_core.o /home/xavier/ricm/mul_projet/py2stm/print/usbd_core.o /home/xavier/ricm/mul_projet/py2stm/print/usb_dcd_int.o  /home/xavier/ricm/mul_projet/py2stm/print/stm32f4xx_it.o /home/xavier/ricm/mul_projet/py2stm/print/stm32f4_discovery.o
	${GCC_PATH}/arm-none-eabi-objcopy -O binary ${BUILD_PATH}/${PRO_NAME}.elf ${BUILD_PATH}/${PRO_NAME}.bin

clean:
	rm -f *.o *.bin *.elf

burn:
	$(STLINK)/st-flash write $(PRO_NAME).bin 0x8000000

