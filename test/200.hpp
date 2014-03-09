#ifndef __200_HPP
#define __200_HPP

using namespace __shedskin__;

namespace __200__ { /* XXX */
class moeha;
class MyClass;
class Common;
class Decoder;
}
namespace __200__ {

extern str *const_0, *const_1, *const_10, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

class Common;
class Decoder;
class moeha;
class MyClass;

typedef __ss_int (*lambda0)(void *, void *, void *, void *, void *);
typedef __ss_int (*lambda1)(__ss_int, __ss_int);

extern Decoder *d;
extern str *__name__;
extern __os__::popen_pipe *f;
extern tuple2<list<__ss_int> *, list<__ss_int> *> *__0, *__1;
extern list<__ss_int> *rFDs, *wFDs, *xFDs;


extern class_ *cl_Common;
class Common : public pyobj {
public:
    static __ss_int CostScale;

    __array__::array<__ss_int> *lzpLow;

    Common() {}
    Common(void *inputStream, void *outputStream, void *options) {
        this->__class__ = cl_Common;
        __init__(inputStream, outputStream, options);
    }
    static void __static__();
    void *__init__(void *inputStream, void *outputStream, void *options);
};

extern class_ *cl_Decoder;
class Decoder : public Common {
public:

    Decoder() {}
    Decoder(void *inputStream, void *outputStream, void *options) {
        this->__class__ = cl_Decoder;
        __init__(inputStream, outputStream, options);
    }
    void *__init__(void *inputStream, void *outputStream, void *options);
};

extern class_ *cl_moeha;
class moeha : public pyobj {
public:
    static __ss_int i;
    static list<__ss_int> *l;
    static __ss_int __5;
    static __ss_int __4;
    static list<list<double> *> *y;
    static __ss_int x;

    moeha() { this->__class__ = cl_moeha; }
    static void __static__();
};

extern class_ *cl_MyClass;
class MyClass : public pyobj {
public:
    static __ss_int A;
    static __ss_int C;
    static __ss_int B;
    static __ss_int t2;
    static __ss_int v2;
    static tuple2<__ss_int, __ss_int> *__11;
    static tuple2<__ss_int, __ss_int> *__10;
    static tuple2<__ss_int, __ss_int> *__7;
    static list<__ss_int> *__6;
    static __ss_int t;
    static __ss_int zz;
    static __ss_int v;
    static tuple2<__ss_int, __ss_int> *y;
    static __ss_int x;
    static __ss_int z;
    static tuple2<__ss_int, __ss_int> *__9;
    static __ss_int __8;

    MyClass() { this->__class__ = cl_MyClass; }
    static void __static__();
};

extern lambda1  default_0;

void *bla(lambda1 hop);

} // module namespace
#endif
