#pragma  once

#include "__zz_cib_internal/example-predef.h"

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
		A(A&& rhs);
	public:
		A();
		A(const A& );
		~A();
		//! This is to know what cib does with virtual functions.
		virtual void VirtFunc();
		//! Doesn't do anything meaningful
		//! @note It is just for explaining how cib works.
		void SomeFunc();

	private:
		__ZZ_CIB_CLASS_INTERNAL_DEF(A, Example::A);
	};
	class B : public ::Example::A
	{
	public:
		B(B&& rhs);
	public:
		B();
		B(const B& );
		~B();
		virtual void VirtFunc();

	private:
		__ZZ_CIB_CLASS_INTERNAL_DEF(B, Example::B);
	};
}

#include "__zz_cib_internal/example-impl.h"
