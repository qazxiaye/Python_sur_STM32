extern "C" {
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>


#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"


__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

void __wrap___aeabi_unwind_cpp_pr0() {}

volatile uint32_t time_var1, time_var2;

void timing_handler() {
	if (time_var1) {
		time_var1--;
	}

	time_var2++;
}

//Quick hack, approximately 1ms delay
void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=5971;
      while (x-- > 0)
         __asm("nop");
   }
}

//Flash orange LED at about 1hz
int main(void)
{
    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable the clock to GPIOD
    //GPIOD->MODER = (1 << 26);             // set pin 13 to be general purpose output
    //GPIOD->MODER = 0x55000000;


	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);


	// ------------- USB -------------- //
	USBD_Init(&USB_OTG_dev,
	            USB_OTG_FS_CORE_ID,
	            &USR_desc,
	            &USBD_CDC_cb,
	            &USR_cb);

	setbuf(stdout, NULL);


    for (;;) {
       ms_delay(500);
	   STM_EVAL_LEDToggle(LED3);
	   STM_EVAL_LEDToggle(LED4);
	   STM_EVAL_LEDToggle(LED5);
	   STM_EVAL_LEDToggle(LED6);
	   printf("qqqq\n");
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


}
