#pragma once

namespace __zz_cib_ { namespace RValueExample {
  //#= FullClassName: ::RValueExample
  enum { __zz_cib_classid = 1 };
}}

namespace __zz_cib_ { namespace Example {
  enum { __zz_cib_next_class_id = 2 };
}}

namespace __zz_cib_ { namespace RValueExample { namespace __zz_cib_methodid {
  enum {
    //#= ~RValueExample();
    __zz_cib_delete_0 = 0,
    //#= RValueExample(std::int32_t);
    __zz_cib_new_1 = 1,
    //#= RValueExample(::RValueExample&&);
    __zz_cib_new_2 = 2,
    //#= RValueExample(::RValueExample const &);
    __zz_cib_copy_3 = 3,
    //#= ::RValueExample& operator=(::RValueExample&&);
    __zz_cib_OperatorEqual_4 = 4,
    //#= ::RValueExample& operator=(::RValueExample const &);
    __zz_cib_OperatorEqual_5 = 5,
    //#= std::int32_t Set(::RValueExample&&);
    Set_6 = 6,
    //#= std::int32_t GetValue() const;
    GetValue_7 = 7,
    __zz_cib_next_method_id = 8
  };
}}}

