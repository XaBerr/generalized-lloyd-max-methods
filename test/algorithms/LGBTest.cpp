#include "../../src/include.h"
#include "../catch.hpp"

TEST_CASE("LGB LGB()", "[]") {
  LGB<int> quantizer;
  REQUIRE(quantizer.rate != 0);
}