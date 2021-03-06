#pragma once
#include <vector>

class C
{
public:
  C(int x);
  virtual ~C() = default;

public:
  virtual int f() const {
    return m;
  }

private:
  char disturbSize[11];
  int m;
};

class A
{
public:
  A();
  
public:
  // std::vector<int> f() const {
  //   return {2, 3, 9};
  // }


public:
  std::vector<C> g() const {
    std::vector<C> ret;
    ret.emplace_back(11);
    ret.emplace_back(101);
    return ret;
  }
};
