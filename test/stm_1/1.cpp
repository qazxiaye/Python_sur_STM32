#include "builtin.hpp"
#include "1.hpp"

namespace __1__ {


str *__name__;
__ss_int aap;



__ss_int ident(__ss_int x) {
    
    return x;
}

__ss_int boing(__ss_int c, double d) {
    
    return ident(c);
}

void __init() {
    __name__ = new str("__main__");

    aap = boing(1, 1.0);
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __shedskin__::__start(__1__::__init);
}
