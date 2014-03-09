#include "builtin.hpp"
#include "100.hpp"
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

namespace __100__ {


str *__name__;



void __init() {
    __name__ = new str("__main__");

    print2(NULL,0,1, ___box(___bool(__eq((new list<__ss_int>(2,1,2)), (new list<__ss_int>(2,1,2))))));
    print2(NULL,0,1, ___box(___bool(__eq((new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2,1,2)),(new tuple2<__ss_int, __ss_int>(2,2,3)))), (new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2,1,2)),(new tuple2<__ss_int, __ss_int>(2,2,3))))))));
    print2(NULL,0,1, ___box(___bool(__eq((new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2,1,4)),(new tuple2<__ss_int, __ss_int>(2,2,3)))), (new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2,1,2)),(new tuple2<__ss_int, __ss_int>(2,2,3))))))));
    print2(NULL,0,1, ___box(___bool(((new tuple2<__ss_int, __ss_int>(3,1,2,3)))->__contains__(1))));
    print2(NULL,0,1, ___box(___bool(((new tuple2<__ss_int, __ss_int>(2,1,2)))->__contains__(1))));
    print2(NULL,0,1, ___box(___bool(((new tuple2<__ss_int, __ss_int>(2,1,2)))->__contains__(3))));
    print2(NULL,0,1, ___box(___bool(((new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2,1,2)),(new tuple2<__ss_int, __ss_int>(2,2,3)))))->__contains__((new tuple2<__ss_int, __ss_int>(2,1,2))))));
    print2(NULL,0,1, ___box(___bool(((new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2,1,2)),(new tuple2<__ss_int, __ss_int>(2,2,3)))))->__contains__((new tuple2<__ss_int, __ss_int>(2,1,4))))));
    print2(NULL,0,1, ___box(___bool(((new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(1,2)),(new tuple2<__ss_int, __ss_int>(1,1)))))->__contains__((new tuple2<__ss_int, __ss_int>(1,1))))));
    print2(NULL,0,1, ___box(___bool(((new list<tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(1,2)),(new tuple2<__ss_int, __ss_int>(1,1)))))->__contains__((new tuple2<__ss_int, __ss_int>(1,3))))));
    print2(NULL,0,1, ___box(___bool(((new tuple2<list<__ss_int> *, list<__ss_int> *>(2,(new list<__ss_int>(1,2)),(new list<__ss_int>(1,1)))))->__contains__((new list<__ss_int>(1,1))))));
}

} // module namespace

int main(int, char **) {

    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
    setbuf(stdout, NULL);
    __shedskin__::__init();
    __shedskin__::__start(__100__::__init);
}
