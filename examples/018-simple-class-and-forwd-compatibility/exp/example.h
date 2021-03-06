#pragma  once

#include "__zz_cib_internal/example-predef.h"

//! Contains example definitions to explain cib's functioning
namespace Example
{
  //! A vividly trivial class
  //! Contains just a simple method.
  class A
  {
  public:
    A(A&& rhs);
  public:
    A(const A& );
    ~A();
    A();
    //! Doesn't do anything meaningful
    //! @note It is just for explaining how cib works.
    int SomeFunc();
    //! Adde method in new version
    int AnotherFunction();

  private:
    __ZZ_CIB_PROXY_CLASS_INTERNALS(A, Example::A);
  };
}

#include "__zz_cib_internal/example-postdef.h"
