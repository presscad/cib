#pragma once

namespace __zz_cib_ { namespace Example { namespace A {
  //#= FullClassName: ::Example::A
  enum { __zz_cib_classid = 256 };
}}}

namespace __zz_cib_ { namespace Example {
  enum { __zz_cib_next_class_id = 257 };
  enum { __zz_cib_internal_class_id = 1 };
}}

namespace __zz_cib_ { namespace Example { namespace A { namespace __zz_cib_methodid {
  enum {
    //#= A(::Example::A const &);
    __zz_cib_copy = 0,
    //#= ~A();
    __zz_cib_delete = 1,
    //#= A();
    __zz_cib_new = 2,
    //#= ::Example::A& operator <<(int);
    __zz_cib_OperatorLShift = 3,
    //#= ::Example::A& operator >>(int&);
    __zz_cib_OperatorRShift = 4,
    __zz_cib_next_method_id = 5
  };
}}}}
