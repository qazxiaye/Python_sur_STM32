#include "builtin.hpp"
#include "2.hpp"

namespace __2__ {


str *__name__;
fred *x;



/**
class fred
*/

class_ *cl_fred;

void fred::__static__() {
}

void __init() {
    __name__ = new str("__main__");

    cl_fred = new class_("fred");
    fred::__static__();
    x = (new fred());
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __shedskin__::__start(__2__::__init);
}
