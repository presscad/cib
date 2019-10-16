#pragma once

#include <cassert>
#include <memory>

class I
{
public:
  virtual ~I() {}
public:
  virtual int f() const = 0;
  virtual std::unique_ptr<int> g() const = 0;
};

class A
{
public:
  A();
public:
  std::unique_ptr<I> f() const {
    class M : public I {
      int f() const override {
        return 909;
      }

      std::unique_ptr<int> g() const override {
        return nullptr;
      }
    };
    return std::make_unique<M>();
  }

  I* g() {
    return nullptr;
  }

  int h(std::unique_ptr<I> p) const {
    auto g = p->g();
    assert(*g == 5);
    return p->f();
  }

  int i(I* p) const {
    return p->f();
  }
};
