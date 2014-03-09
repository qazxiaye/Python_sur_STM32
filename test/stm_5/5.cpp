#include "builtin.hpp"
#include "5.hpp"
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

namespace __5__ {

str *const_0;


str *__name__, *c;
fred *b;



/**
class fred
*/

class_ *cl_fred;

str *fred::speak(str *x) {
    
    return x;
}

void __init() {
    const_0 = new str("goedzo!");

    __name__ = new str("__main__");

    cl_fred = new class_("fred");
    b = (new fred());
    c = b->speak(const_0);
}

} // module namespace

int main(int, char **) {

    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
    setbuf(stdout, NULL);
    __shedskin__::__init();
    __shedskin__::__start(__5__::__init);
}
