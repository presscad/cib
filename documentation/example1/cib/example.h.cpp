#include "example.h"

#include "__zz_cib_Example-ids.h"
#include "__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_Example-proxy.h"

namespace __zz_cib_ { namespace Example { namespace A {
	static ::Example::A* __zz_cib_decl __zz_cib_new_0() {
		return new ::Example::A();
	}
	static ::Example::A* __zz_cib_decl __zz_cib_copy_1(const ::Example::A* __zz_cib_param0) {
		return new ::Example::A(*__zz_cib_param0);
	}
	static void __zz_cib_decl __zz_cib_delete_2(::Example::A* __zz_cib_obj) {
		delete __zz_cib_obj;
	}
	static void __zz_cib_decl SomeFunc_3(::Example::A* __zz_cib_obj) {
		__zz_cib_obj->::Example::A::SomeFunc();
	}
}}}

namespace __zz_cib_ { namespace Example { namespace A {
	const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
		static const __zz_cib_MTableEntry methodArray[] = {
			reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_new_0),
			reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_copy_1),
			reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_delete_2),
			reinterpret_cast<__zz_cib_MTableEntry> (&SomeFunc_3)
		};
		static const __zz_cib_MethodTable methodTable = { methodArray, 4 };
		return &methodTable;
	}
}}}
