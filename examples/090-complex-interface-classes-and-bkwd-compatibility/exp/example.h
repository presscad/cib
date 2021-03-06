#pragma  once

#include "__zz_cib_internal/example-predef.h"

class Interface2;
class Interface3;
class Interface1
{
public:
  Interface1(Interface1&& rhs);
public:
  virtual int disruptVTable();
  virtual Interface2* p() = 0;
  virtual Interface3& r() = 0;
  virtual ~Interface1();
protected:
  Interface1();

private:
  __ZZ_CIB_PROXY_CLASS_INTERNALS(Interface1, Interface1);
};

class Interface2
{
public:
  Interface2(Interface2&& rhs);
public:
  virtual int disruptVTable();
  virtual int f() = 0;
  virtual ~Interface2();
protected:
  Interface2();

private:
  __ZZ_CIB_PROXY_CLASS_INTERNALS(Interface2, Interface2);
};

class Interface3
{
public:
  Interface3(Interface3&& rhs);
public:
  virtual int disruptVTable();
  virtual int g() = 0;
  virtual ~Interface3();
protected:
  Interface3();

private:
  __ZZ_CIB_PROXY_CLASS_INTERNALS(Interface3, Interface3);
};

class A
{
public:
  A(A&& rhs);
public:
  A(const A& );
  ~A();
  A();
  int SetInterface(Interface1* pInterface1) const;

private:
  __ZZ_CIB_PROXY_CLASS_INTERNALS(A, A);
};

#include "__zz_cib_internal/example-postdef.h"
