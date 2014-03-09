#include "builtin.hpp"
#include "3.hpp"

namespace __3__ {


str *__name__;
__ss_int a, h;



double ident(double x) {
    
    return x;
}

double boing(double c, double d) {
    
    return ident(c);
}

void __init() {
    __name__ = new str("__main__");

    a = 1;
    h = boing(((double)(boing(((double)(a)), 1.0))), boing(3.0, ((double)(a))));
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __shedskin__::__start(__3__::__init);
}
