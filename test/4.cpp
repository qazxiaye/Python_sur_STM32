#include "builtin.hpp"
#include "4.hpp"

namespace __4__ {


list<__ss_int> *a;
str *__name__;



void __init() {
    __name__ = new str("__main__");

    a = (new list<__ss_int>(1,1));
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __shedskin__::__start(__4__::__init);
}
