#pragma once

namespace __zz_cib_ { namespace Example { namespace A {
  //#= FullClassName: ::Example::A
  enum { __zz_cib_classid = 1 };
}}}

namespace __zz_cib_ { namespace Example { namespace Int {
  //#= FullClassName: ::Example::Int
  enum { __zz_cib_classid = 2 };
}}}

namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class3 {
  //#= FullClassName: ::Example::Value<::Example::Int>
  enum { __zz_cib_classid = 3 };
}}}

namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class4 {
  //#= FullClassName: ::Example::Value<int>
  enum { __zz_cib_classid = 4 };
}}}

namespace __zz_cib_ { namespace Example {
  enum { __zz_cib_next_class_id = 5 };
}}

namespace __zz_cib_ { namespace Example { namespace A { namespace __zz_cib_methodid {
  enum {
    //#= A();
    __zz_cib_new_0 = 0,
    //#= A(::Example::A const &);
    __zz_cib_copy_1 = 1,
    //#= ~A();
    __zz_cib_delete_2 = 2,
    //#= void Set(::Example::Value<int> const &);
    Set_3 = 3,
    //#= ::Example::Value<int> Get() const;
    Get_4 = 4,
    //#= void SetInt(::Example::Value<::Example::Int> const &);
    SetInt_5 = 5,
    //#= ::Example::Value<::Example::Int> GetInt() const;
    GetInt_6 = 6,
    __zz_cib_next_method_id = 7
  };
}}}}

namespace __zz_cib_ { namespace Example { namespace Int { namespace __zz_cib_methodid {
  enum {
    //#= Int(::Example::Int const &);
    __zz_cib_copy_0 = 0,
    //#= ~Int();
    __zz_cib_delete_1 = 1,
    //#= Int(int);
    __zz_cib_new_2 = 2,
    //#= operator int () const;
    __zz_cib_Operator_3 = 3,
    __zz_cib_next_method_id = 4
  };
}}}}

namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class3 { namespace __zz_cib_methodid {
  enum {
    //#= Value(::Example::Value<::Example::Int> const &);
    __zz_cib_copy_0 = 0,
    //#= ~Value();
    __zz_cib_delete_1 = 1,
    //#= Value(::Example::Int);
    __zz_cib_new_2 = 2,
    //#= ::Example::Int GetValue() const;
    GetValue_3 = 3,
    //#= void SetValue(::Example::Int);
    SetValue_4 = 4,
    __zz_cib_next_method_id = 5
  };
}}}}

namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class4 { namespace __zz_cib_methodid {
  enum {
    //#= Value(::Example::Value<int> const &);
    __zz_cib_copy_0 = 0,
    //#= ~Value();
    __zz_cib_delete_1 = 1,
    //#= Value(int);
    __zz_cib_new_2 = 2,
    //#= int GetValue() const;
    GetValue_3 = 3,
    //#= void SetValue(int);
    SetValue_4 = 4,
    __zz_cib_next_method_id = 5
  };
}}}}

