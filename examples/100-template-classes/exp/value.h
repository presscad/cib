#pragma  once

#include "__zz_cib_internal/value-predef.h"

namespace Example
{
  template <typename _T>
  class Value
  {
  public:
    Value(_T x = _T())
      : x_(x)
    {
    }
    _T GetValue() const
    {
      return x_;
    }
    void SetValue(_T x)
    {
      x_ = x;
    }
    bool operator ==(const Value& rhs) const
    {
      return x_ == rhs.x_;
    }
  private:
    _T x_;
  };
}

#include "__zz_cib_internal/value-postdef.h"
