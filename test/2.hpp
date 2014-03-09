#ifndef __2_HPP
#define __2_HPP

using namespace __shedskin__;
namespace __2__ {

class fred;


extern fred *x;
extern str *__name__;


extern class_ *cl_fred;
class fred : public pyobj {
public:
    fred() { this->__class__ = cl_fred; }
    static void __static__();
};


} // module namespace
#endif
