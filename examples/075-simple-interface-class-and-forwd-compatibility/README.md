## Simple Interface Class and Forward Compatibility

In example `Simple Interface Class` we have only tackled the cases that is very much expected from a C++ library/program. In this example we will see how CIB ensures ABI stability in the case when virtual table of it's interface class is disrupted. This example is actually next version of previous, `Simple Interface Class`, example.

Below I am showing the diff of new header with previous one.

```diff
--- 060-simple-interface-class/pub/example.h
+++ 070-simple-interface-class-and-bkwd-compatibility/pub/example.h
@@ -1,18 +1,38 @@
 #pragma once
 
+#include <functional>
+
 class Interface
 {
 public:
+  //! Just to disrupt vtable.
+  virtual int Gunc() = 0;
   virtual int Func() = 0;
+
   virtual ~Interface() {}
 };
 
 class A
 {
 public:
   A();
   int UseInterface(Interface* pInterface) const
   {
-    return pInterface->Func();
+    return pInterface->Func() + CallNewMethod(pInterface);
+  }
+
+private:
+  int CallNewMethod(Interface* pInterface) const
+  {
+    try
+    {
+      // new client
+      return pInterface->Gunc();
+    }
+    catch (std::bad_function_call&)
+    {
+      // old client
+      return 0;
+    }
   }
 };

```

As it can be seen that only new virtual methods are added to an existing interface. But the new virtual method is added before the existing one and that is the key change. If CIB architecture is not used then such change will break the binary compatibility.

Below is the diff of client code from the previous example:

```diff
7a8
>   int Gunc() override { return 193; };
15c16
<   CHECK(a.UseInterface(&i) == 167);
---
>   CHECK(a.UseInterface(&i) == 167 + 193);
17a19,24
> TEST_CASE("Interface callback: new method should be available to new clients")
> {
>   A a;
>   Implement i;
>   CHECK(i.Gunc() == 193);
> }

```

There is no surprise that this new client will work with new library. But the old client, the client of previous example `simple-interface-class`, should continue working with new library without any change or recompilation. The automated test `simple-interface-class-and-bkwd-compatibility` ensures the client of `simple-interface-class` works with library of this example.

The reason of this **ABI stability** is that virtual tables are not shared across components. CIB shares **MethodTable** instead. Let's see the diff of MethodTable of new library:

```diff

```

As it can be seen that the new method caused a new entry in MethodTable and that happened at the very end of the table, irrespective of the fact that new virtual function was added before the existing one. **So, the older client will continue seeing the MethodTable precisely how they expects it to be and that ensures ABI stability**.

### Running CIB
To make CIB ensures ABI stability we needed to run cib with additional parameter and supply ID file of previous example:

```sh
cib -i pub -o exp -b cib -m Example -c ../060-simple-interface-class/cib/__zz_cib_Example-ids.h
```

This makes cib understand that we want ABI stability with previous example and CIB generates glue code accordingly.

