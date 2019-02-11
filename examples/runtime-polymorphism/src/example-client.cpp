#include "example.h"

#include <catch/catch.hpp>

TEST_CASE("Virtual function call across library")
{
  A* pA = new B();

  REQUIRE(pA->VirtFunc() == 15);    // Generated instruction will effectively call `pA->B::VirtFunc()`
  REQUIRE(pA->A::VirtFunc() == 10); // A regular call without use of virtual table.
  REQUIRE(pA->SomeFunc() == 5);     // Non-virtual call.
}
