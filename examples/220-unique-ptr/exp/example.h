#pragma  once
#include <cassert>
#include <memory>

#include "__zz_cib_internal/example-predef.h"

class I
{
public:
  I(I&& rhs);
public:
  I(std::unique_ptr<int> pi);
  I();
  virtual ~I();
  virtual int f() const = 0;
  virtual std::unique_ptr<int> g() const = 0;

private:
  __ZZ_CIB_CLASS_INTERNAL_DEF(I, __zz_cib_Class257);
};

class A
{
public:
  A(A&& rhs);
public:
  A(A const & );
  ~A();
  A();
  std::unique_ptr<I> f() const;
  I* g();
  int h(std::unique_ptr<I> p) const;
  int i(I* p) const;
  int j(std::unique_ptr<I>* pp);

private:
  __ZZ_CIB_CLASS_INTERNAL_DEF(A, __zz_cib_Class258);
};

#include "__zz_cib_internal/example-postdef.h"
