#include "builtin.hpp"
#include "110.hpp"

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
    __shedskin__::__init();
    __shedskin__::__start(__110__::__init);
}
