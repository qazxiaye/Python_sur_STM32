#include "builtin.hpp"
#include "100.hpp"

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
    __shedskin__::__init();
    __shedskin__::__start(__100__::__init);
}
