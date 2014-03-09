#ifndef __10_HPP
#define __10_HPP

using namespace __shedskin__;
namespace __10__ {

extern str *const_0;

class fred;


extern __ss_int b;
extern fred *a, *c;
extern str *__name__, *d;


extern class_ *cl_fred;
class fred : public pyobj {
public:
    str *_a;
    __ss_int hallo;

    fred() { this->__class__ = cl_fred; }
    static void __static__();
};


} // module namespace
#endif
