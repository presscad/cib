#pragma once

namespace __zz_cib_ { namespace A {
  //#= FullClassName: ::A
  enum { __zz_cib_classid = 2 };
}}

namespace __zz_cib_ { namespace IF {
  //#= FullClassName: ::IF
  enum { __zz_cib_classid = 1 };
}}

namespace __zz_cib_ { namespace IF { namespace __zz_cib_GenericProxy {
  //#= FullClassName: ::IF::__zz_cib_GenericProxy
  enum { __zz_cib_classid = 3 };
}}}

namespace __zz_cib_ { namespace Example {
  enum { __zz_cib_next_class_id = 4 };
}}

namespace __zz_cib_ { namespace A { namespace __zz_cib_methodid {
  enum {
    //#= A(::A const &);
    __zz_cib_copy_0 = 0,
    //#= ~A();
    __zz_cib_delete_1 = 1,
    //#= A();
    __zz_cib_new_2 = 2,
    //#= int SetIF(::IF*);
    SetIF_3 = 3,
    //#= ::IF* GetIF() const;
    GetIF_4 = 4,
    __zz_cib_next_method_id = 5
  };
}}}

namespace __zz_cib_ { namespace IF { namespace __zz_cib_methodid {
  enum {
    //#= IF();
    __zz_cib_new_0 = 0,
    //#= int ProtectedPureVirtual();
    ProtectedPureVirtual_1 = 1,
    //#= int ProtectedVirtual();
    ProtectedVirtual_2 = 2,
    //#= int ProtectedNonVirtual();
    ProtectedNonVirtual_3 = 3,
    //#= int PublicPureVirtual();
    PublicPureVirtual_4 = 4,
    //#= int PublicVirtual();
    PublicVirtual_5 = 5,
    //#= int PublicNonVirtual();
    PublicNonVirtual_6 = 6,
    //#= ~IF();
    __zz_cib_delete_7 = 7,
    //#= int PrivatePureVirtual();
    PrivatePureVirtual_8 = 8,
    //#= int PrivateVirtual();
    PrivateVirtual_9 = 9,
    //#= __zz_cib_get_class_id
    __zz_cib_get_class_id_10 = 10,
    //#= __zz_cib_release_proxy
    __zz_cib_release_proxy_11 = 11,
    __zz_cib_next_method_id = 12
  };
}}}

namespace __zz_cib_ { namespace IF { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
  enum {
    //#= int PrivatePureVirtual();
    PrivatePureVirtual_0 = 0,
    //#= int PrivateVirtual();
    PrivateVirtual_1 = 1,
    //#= int ProtectedPureVirtual();
    ProtectedPureVirtual_2 = 2,
    //#= int ProtectedVirtual();
    ProtectedVirtual_3 = 3,
    //#= int PublicPureVirtual();
    PublicPureVirtual_4 = 4,
    //#= int PublicVirtual();
    PublicVirtual_5 = 5,
    //#= ~IF();
    __zz_cib_delete_6 = 6,
    __zz_cib_next_method_id = 7
  };
}}}}

