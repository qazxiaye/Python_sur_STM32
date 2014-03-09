#include "builtin.hpp"
#include "110.hpp"
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

namespace __110__ {

str *const_0;


str *__name__;
list<list<__ss_int> *> *puzzlecolumns, *puzzlerows;



void *row_perm_rec(list<__ss_int> *numbers) {
    
    range(numbers->__getfast__(0));
    return NULL;
}

void __init() {
    const_0 = __char_cache[117];;

    __name__ = new str("__main__");

    puzzlecolumns = (new list<list<__ss_int> *>(1,(new list<__ss_int>(1,7))));
    puzzlerows = (new list<list<__ss_int> *>(1,(new list<__ss_int>(1,8))));
    (new list<str *>(1,const_0));
    row_perm_rec(puzzlerows->__getfast__(0));
}

} // module namespace

int main(int, char **) {

    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
    setbuf(stdout, NULL);
    __shedskin__::__init();
    __shedskin__::__start(__110__::__init);
}
