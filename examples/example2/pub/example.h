#pragma once

//! Contains example definitions to explain cib's functioning
//! @attention
//! This example is like next version of example-1.
//! The compiled library of this example will remain binary
//! compatible with client of previous example.
namespace Example
{

  //! Example to see what cib does for classes with virtual methods.
  class A
  {
  public:
    //! This is to know what cib does with virtual functions.
    virtual int VirtFunc();
    //! Doesn't do anything meaningful
    //! @note It is just for explaining how cib works.
    int SomeFunc();

    virtual ~A() {}
  };

  class B : public A
  {
  public:
    int VirtFunc() override;
  };

}
