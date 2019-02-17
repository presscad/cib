#include "example.h"

#include <catch/catch.hpp>

#include <type_traits>

TEST_CASE("Passed fptr should be invoked.")
{
  A a;
  CHECK(a.F1([]() {return 101;}) == 101);
}
