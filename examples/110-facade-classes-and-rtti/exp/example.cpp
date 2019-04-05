#include "example.h"


Facade::Facade(__zz_cib_::__zz_cib_HANDLE* h)
  : __zz_cib_h_(h)
{
  __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

Facade::Facade(Facade&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
  __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

Facade::~Facade() {
  auto h = __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_release_handle(this);
  __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_delete_1(h);
}

PublicFacadeImpl::PublicFacadeImpl(__zz_cib_::__zz_cib_HANDLE* h)
  : ::Facade(__zz_cib_::PublicFacadeImpl::__zz_cib_Helper::__zz_cib_cast_to___Facade_4(h))
  , __zz_cib_h_(h)
{}

PublicFacadeImpl::PublicFacadeImpl(PublicFacadeImpl&& rhs)
  : ::Facade(std::move(rhs))
  , __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
}

PublicFacadeImpl::PublicFacadeImpl(::PublicFacadeImpl const & __zz_cib_param0)
  : PublicFacadeImpl(__zz_cib_::PublicFacadeImpl::__zz_cib_Helper::__zz_cib_copy_0(__zz_cib_::PublicFacadeImpl::__zz_cib_Helper::__zz_cib_handle(__zz_cib_param0)))
{}

PublicFacadeImpl::~PublicFacadeImpl() {
  auto h = __zz_cib_::PublicFacadeImpl::__zz_cib_Helper::__zz_cib_release_handle(this);
  __zz_cib_::PublicFacadeImpl::__zz_cib_Helper::__zz_cib_delete_1(h);
}

PublicFacadeImpl::PublicFacadeImpl()
  : PublicFacadeImpl(__zz_cib_::PublicFacadeImpl::__zz_cib_Helper::__zz_cib_new_2())
{}

void PublicFacadeImpl::F() {
  __zz_cib_::PublicFacadeImpl::__zz_cib_Helper::F_3(__zz_cib_h_);
}

A::A(__zz_cib_::__zz_cib_HANDLE* h)
  : __zz_cib_h_(h)
{}

A::A(A&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
}

A::A(::A const & __zz_cib_param0)
  : A(__zz_cib_::A::__zz_cib_Helper::__zz_cib_copy_0(__zz_cib_::A::__zz_cib_Helper::__zz_cib_handle(__zz_cib_param0)))
{}

A::~A() {
  auto h = __zz_cib_::A::__zz_cib_Helper::__zz_cib_release_handle(this);
  __zz_cib_::A::__zz_cib_Helper::__zz_cib_delete_1(h);
}

A::A()
  : A(__zz_cib_::A::__zz_cib_Helper::__zz_cib_new_2())
{}

::Facade* A::PublicFacade() {
  return __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_from_handle(
    __zz_cib_::A::__zz_cib_Helper::PublicFacade_3(__zz_cib_h_)
  );
}

::Facade* A::PrivateFacade1() {
  return __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_from_handle(
    __zz_cib_::A::__zz_cib_Helper::PrivateFacade1_4(__zz_cib_h_)
  );
}

::Facade* A::PrivateFacade2() {
  return __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_from_handle(
    __zz_cib_::A::__zz_cib_Helper::PrivateFacade2_5(__zz_cib_h_)
  );
}
namespace __zz_cib_ { namespace Facade { namespace __zz_cib_Generic {
class Facade : public ::Facade {
  __zz_cib_HANDLE* __zz_cib_h_;

  using __zz_cib_TYPE = __zz_cib_HANDLE;
  static __zz_cib_::__zz_cib_MethodTableHelper& __zz_cib_get_mtable_helper() {
    static __zz_cib_::__zz_cib_MethodTableHelper mtableHelper(__zz_cib_Example_GetMethodTable(
      __zz_cib_classid));
    return mtableHelper;
  }
  explicit Facade(__zz_cib_HANDLE* h) : ::Facade(h), __zz_cib_h_(h) {}
public:
  static ::Facade* __zz_cib_from_handle(__zz_cib_HANDLE* h) {
    return new Facade(h);
  }
  void F() override {
    using FProc = void (__zz_cib_decl *) (__zz_cib_TYPE*);
    return __zz_cib_get_mtable_helper().invoke<FProc, __zz_cib_methodid::F_0>(
      __zz_cib_h_);
  }
  ~Facade() override {
    if (!__zz_cib_h_) return;
    using __zz_cib_deleteProc = void (__zz_cib_decl *) (__zz_cib_TYPE*);
    __zz_cib_get_mtable_helper().invoke<__zz_cib_deleteProc, __zz_cib_methodid::__zz_cib_delete_1>(
      __zz_cib_h_);
  }
};
}}}
::Facade* __zz_cib_::Facade::__zz_cib_Helper::__zz_cib_create_proxy(__zz_cib_HANDLE* h) {
  switch(__zz_cib_get_class_id(&h)) {
  case __zz_cib_::PublicFacadeImpl::__zz_cib_classid:
    return __zz_cib_::PublicFacadeImpl::__zz_cib_Helper::__zz_cib_from_handle(h);
  default:
    return ::__zz_cib_::Facade::__zz_cib_Generic::Facade::__zz_cib_from_handle(h);
  }
}
