#pragma once

namespace __zz_cib_ { namespace A {
  //#= FullClassName: ::A
  enum { __zz_cib_classid = 1 };
}}

namespace __zz_cib_ { namespace B {
  //#= FullClassName: ::B
  enum { __zz_cib_classid = 2 };
}}

namespace __zz_cib_ { namespace Example {
  enum { __zz_cib_next_class_id = 3 };
}}

namespace __zz_cib_ { namespace A { namespace __zz_cib_methodid {
  enum {
    //#= A(::A const &);
    __zz_cib_copy_0 = 0,
    //#= ~A();
    __zz_cib_delete_1 = 1,
    //#= A(int);
    __zz_cib_new_2 = 2,
    __zz_cib_next_method_id = 3
  };
}}}

namespace __zz_cib_ { namespace B { namespace __zz_cib_methodid {
  enum {
    //#= B();
    __zz_cib_new_0 = 0,
    //#= B(::B const &);
    __zz_cib_copy_1 = 1,
    //#= ~B();
    __zz_cib_delete_2 = 2,
    //#= void SetA(::A*);
    SetA_3 = 3,
    //#= ::A* GetA() const;
    GetA_4 = 4,
    __zz_cib_next_method_id = 5
  };
}}}

