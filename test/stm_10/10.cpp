#include "builtin.hpp"
#include "10.hpp"

namespace __10__ {

str *const_0;


str *__name__, *d;
__ss_int b;
fred *a, *c;



/**
class fred
*/

class_ *cl_fred;

void fred::__static__() {
}

void __init() {
    const_0 = new str("god");

    __name__ = new str("__main__");

    cl_fred = new class_("fred");
    fred::__static__();
    a = (new fred());
    a->hallo = 1;
    b = a->hallo;
    c = (new fred());
    c->_a = const_0;
    d = c->_a;
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __shedskin__::__start(__10__::__init);
}
