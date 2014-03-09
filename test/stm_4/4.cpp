#include "builtin.hpp"
#include "4.hpp"
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
}

namespace __4__ {


list<__ss_int> *a;
str *__name__;



void __init() {
    __name__ = new str("__main__");

    a = (new list<__ss_int>(1,1));
}

} // module namespace

int main(int, char **) {

    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
    setbuf(stdout, NULL);
    __shedskin__::__init();
    __shedskin__::__start(__4__::__init);
}
