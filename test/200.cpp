#include "builtin.hpp"
#include "select.hpp"
#include "os/path.hpp"
#include "time.hpp"
#include "array.hpp"
#include "os/__init__.hpp"
#include "stat.hpp"
#include "200.hpp"

namespace __200__ {

str *const_0, *const_1, *const_10, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;


__os__::popen_pipe *f;
list<__ss_int> *rFDs, *wFDs, *xFDs;
Decoder *d;
tuple2<list<__ss_int> *, list<__ss_int> *> *__0, *__1;
str *__name__;


lambda1  default_0;

class list_comp_0 : public __iter<__ss_int> {
public:
    __ss_int _, __2, __3;

    __ss_int lzpLowCount;
    int __last_yield;

    list_comp_0(__ss_int lzpLowCount);
    __ss_int __get_next();
};

static inline __ss_int __lambda1__(__ss_int a, __ss_int b);

list_comp_0::list_comp_0(__ss_int lzpLowCount) {
    this->lzpLowCount = lzpLowCount;
    __last_yield = -1;
}

__ss_int list_comp_0::__get_next() {
    if(!__last_yield) goto __after_yield_0;
    __last_yield = 0;

    FAST_FOR(_,0,lzpLowCount,1,2,3)
        __result = 65461;
        return __result;
        __after_yield_0:;
    END_FOR

    __stop_iteration = true;
}

static inline __ss_int __lambda1__(__ss_int a, __ss_int b) {
    
    return (a+b);
}

/**
class Common
*/

class_ *cl_Common;

void *Common::__init__(void *inputStream, void *outputStream, void *options) {
    __ss_int lzpLowCount;

    lzpLowCount = 10;
    ((Decoder *)this)->lzpLow = (new __array__::array<__ss_int>(const_0, new list_comp_0(lzpLowCount)));
    return NULL;
}

__ss_int Common::CostScale;

void Common::__static__() {
    CostScale = 7;
}

/**
class Decoder
*/

class_ *cl_Decoder;

void *Decoder::__init__(void *inputStream, void *outputStream, void *options) {
    
    Common::__init__(inputStream, outputStream, options);
    return NULL;
}

/**
class moeha
*/

class_ *cl_moeha;

__ss_int moeha::i;
list<__ss_int> *moeha::l;
__ss_int moeha::__5;
__ss_int moeha::__4;
list<list<double> *> *moeha::y;
__ss_int moeha::x;

void moeha::__static__() {
    x = 4;
    print2(NULL,0,1, const_1);
    l = (new list<__ss_int>());

    FAST_FOR(i,0,10,1,4,5)
        l->append(x);
        l->append(i);
    END_FOR

    y = (new list<list<double> *>(1,(new list<double>(1,1.0))));
}

/**
class MyClass
*/

class_ *cl_MyClass;

__ss_int MyClass::A;
__ss_int MyClass::C;
__ss_int MyClass::B;
__ss_int MyClass::t2;
__ss_int MyClass::v2;
tuple2<__ss_int, __ss_int> *MyClass::__11;
tuple2<__ss_int, __ss_int> *MyClass::__10;
tuple2<__ss_int, __ss_int> *MyClass::__7;
list<__ss_int> *MyClass::__6;
__ss_int MyClass::t;
__ss_int MyClass::zz;
__ss_int MyClass::v;
tuple2<__ss_int, __ss_int> *MyClass::y;
__ss_int MyClass::x;
__ss_int MyClass::z;
tuple2<__ss_int, __ss_int> *MyClass::__9;
__ss_int MyClass::__8;

void MyClass::__static__() {
    __6 = range(3);
    A = __6->__getfast__(0);
    B = __6->__getfast__(1);
    C = __6->__getfast__(2);
    __7 = (new tuple2<__ss_int, __ss_int>(2,10,11));
    x = 9;
    y = __7;
    __8 = (B*x);
    z = __8;
    zz = __8;
    __11 = y;
    __9 = y;
    t = __9->__getfirst__();
    t2 = __9->__getsecond__();
    __10 = y;
    v = __10->__getfirst__();
    v2 = __10->__getsecond__();
}

void *bla(lambda1 hop) {
    
    print2(NULL,0,2, const_2, ___box(hop(9, 10)));
    return NULL;
}

void __init() {
    const_0 = __char_cache[72];;
    const_1 = new str("joeh");
    const_2 = new str("ole");
    const_3 = new str("ls");
    const_4 = __char_cache[114];;
    const_5 = new str("hello\000world", 11);
    const_6 = new str("woef%swaf");
    const_7 = new str("waaa\000wa", 7);
    const_8 = new str("woef%swaf%s!");
    const_9 = new str("waaa\000wa\000wa", 10);
    const_10 = new str("\000haaap", 6);

    __name__ = new str("__main__");

    f = __os__::popen(const_3, const_4, (-1));
    __0 = __select__::select((new tuple2<void *, void *>()), (new list<void *>()), (new set<void *>()), 0);
    rFDs = __0->__getfast__(0);
    wFDs = __0->__getfast__(1);
    xFDs = __0->__getfast__(2);
    __1 = __select__::select((new list<__ss_int>(1,f->__ss_fileno())), (new set<void *>()), (new list<void *>()), 20);
    rFDs = __1->__getfast__(0);
    wFDs = __1->__getfast__(1);
    xFDs = __1->__getfast__(2);
    print2(NULL,0,3, ___box(len(rFDs)), ___box(len(wFDs)), ___box(len(xFDs)));
    print2(NULL,0,1, (__time__::asctime())->__slice__(2, 0, 10, 0));
    print2(NULL,0,1, (__str(__time__::localtime()))->__slice__(2, 0, 50, 0));
    print2(NULL,0,1, const_5);
    print2(NULL,0,1, repr(const_5));
    print2(NULL,0,1, repr(__modct(const_6, 1, const_7)));
    print2(NULL,0,1, repr(__modct(const_8, 2, const_9, const_10)));
    cl_Common = new class_("Common");
    Common::__static__();
    cl_Decoder = new class_("Decoder");
    d = (new Decoder(NULL, NULL, NULL));
    print2(NULL,0,1, d->lzpLow);
    cl_moeha = new class_("moeha");
    moeha::__static__();
    print2(NULL,0,1, ___box(moeha::x));
    print2(NULL,0,1, moeha::l);
    print2(NULL,0,1, moeha::y);
    cl_MyClass = new class_("MyClass");
    MyClass::__static__();
    print2(NULL,0,11, ___box(MyClass::A), ___box(MyClass::B), ___box(MyClass::C), ___box(MyClass::x), MyClass::y, ___box(MyClass::z), ___box(MyClass::zz), ___box(MyClass::t), ___box(MyClass::t2), ___box(MyClass::v), ___box(MyClass::v2));
    bla(__lambda1__);
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __stat__::__init();
    __os__::__path__::__init();
    __os__::__init();
    __select__::__init();
    __time__::__init();
    __array__::__init();
    __shedskin__::__start(__200__::__init);
}
