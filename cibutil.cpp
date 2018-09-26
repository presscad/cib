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

#include "cibutil.h"
#include "cibcompound.h"
#include "cibhelper.h"

#include "cppdom.h"

const CibCppCompound* TypeResolver::operator()(const std::string& typeName) const
{
  if (!owner_ || !cppProgram_)
    return nullptr;
  auto* resolvedCppObj = owner_->resolveTypeName(typeName, *cppProgram_);
  return resolvedCppObj && resolvedCppObj->isClassLike() ? static_cast<const CibCppCompound*>(resolvedCppObj) : nullptr;
}

std::string VarTypeResolver::operator()(const std::string& typeName) const
{
  auto resolvedType = TypeResolver::operator()(typeName);
  if (!resolvedType)
    return typeName;
  return isHandle_ ? "__zz_cib::HANDLE" : "::" + resolvedType->fullName();
}
