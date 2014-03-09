#include "builtin.hpp"
#include "5.hpp"

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
    __shedskin__::__init();
    __shedskin__::__start(__5__::__init);
}
