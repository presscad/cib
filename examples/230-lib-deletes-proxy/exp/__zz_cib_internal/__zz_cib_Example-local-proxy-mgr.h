/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "__zz_cib_Example-handle.h"

#include <map>

namespace __zz_cib_
{

template <typename _ProxyClass>
class __zz_cib_local_proxy_mgr
{
public:
  _ProxyClass*& findProxy(__zz_cib_HANDLE* h)
  {
    static _ProxyClass* nullProxy = nullptr;
    auto                itr       = proxyRepo.find(h);
    return (itr == proxyRepo.end()) ? nullProxy : itr->second;
  }
  void addProxy(_ProxyClass* __zz_cib_obj, __zz_cib_HANDLE* h)
  {
    proxyRepo[h] = __zz_cib_obj;
  }
  void removeProxy(__zz_cib_HANDLE* h)
  {
    proxyRepo.erase(h);
  }

private:
  using ProxyRepo = std::map<__zz_cib_HANDLE*, _ProxyClass*>;
  ProxyRepo proxyRepo;
};

}

