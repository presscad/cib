# Examples aka CIB Architecture Details
 We will learn about bits and peices of CIB architecture through code generated by `cib`. We will start with trivial example and slowly build on that to understand what CIB architecture requires in more complex cases. Except the declaration of proxy classes that client's will use, all other code generated by cib are solely for compilers. But we will look into generated code to understand CIB architecture.

**Note**: All examples mentioned below are real programs, however tiny, they are working piece of code and are actually part of automated tests of cib:
- Almost all examples contain a library and a client executable.
- Library consists of a public header and a source file.
- Most functions simply return an `int`.
- `cib` tool is used on public header that
    - generates glue code for library and clients.
    - generates cibified headers that becomes part of the SDK.
- Client is an executable that tests correct behavior of library.

## Types of Examples:
There are 3 types of examples:
- Examples that tests basic C++ feature of cibified SDK.
- Examples that tests cibified SDK offers **backward compatibility**, such tests have `bkwd-compatibility` in it's name.
- Examples that tests cibified SDK offers **forward compatibility**, tests that have `forwd-compatibility` in it's name.

## Example - A Simple Class
This example explains the basic building blocks of CIB architecture and how CIB defines it's own ABI that ensures ABI stability. This example doesn't demonstrate ABI stability yet, which is done in other examples, but it is just to explain the fundamentals of CIB architecture and CIB tool.

For details please see [A Simple Class example](010-simple-class)

## Example - Virtual Function
This example explains how runtime polymorphic calls can be made across component boundary in an ABI stable way. This example too is just to explain required building blocks. In the next example we will consider the ABI stability.

For details please see [Virtual Function example](020-virtual-function)

## Example - Virtual Function and ABI Stability

This is the example that demonstrates how CIB ensures ABI stability even when virtual table is disrupted. This example is built on the previous one and creates a new library with disrupted virtual table. Then it runs both, the new client and also old the client (i.e. the client of previous example). That demostrates that CIB ensures ABI stability when virtual table is disrupted.

For details please see [Virtual Function and ABI Stability example](030-virtual-function-and-bkwd-compatibility)

## Example - Interface Classes

In this example we explore what pieces of architecture should be there to ensure calls made by library to client happens in ABI compatible and stable way.

For details please see [Interface Class example](060-simple-interface-class)

## Example - Interface Classes and ABI Stability

In this example we will see that how ABI stability is guaranteed when virtual table of interface class is disrupted.

For details please see [Interface Class And ABI Sytability example](070-simple-interface-class-and-bkwd-compatibility)

## Example - C++ Template Classes
In this example we consider what CIB architecture needs to do to support template classes and how concretized types of template class can cross component boundary in ABI compatible and stable way.

For details please see [C++ Template Classes example](100-template-classes)

## Example - Facade Classes and RTTI

Please see example `facade-classes-and-rtti` in `examples` folder.

**TODO**: Add detail documentation.

## Example - Non public virtual functions.

Please see example `private-virtuals` in `examples` folder.

**TODO**: Add detail documentation.