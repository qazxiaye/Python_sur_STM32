#ifndef __5_HPP
#define __5_HPP

using namespace __shedskin__;
namespace __5__ {

extern str *const_0;

class fred;


extern fred *b;
extern str *__name__, *c;


extern class_ *cl_fred;
class fred : public pyobj {
public:

    fred() { this->__class__ = cl_fred; }
    str *speak(str *x);
};


} // module namespace
#endif
