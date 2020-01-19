#include "../../src/include.h"
#include "../catch.hpp"
using namespace LGBm;

TEST_CASE("LGBsplit LGBsplit()", "[]") {
  LGBsplit<float> quantizer;
  REQUIRE(quantizer.rate > 0);
  REQUIRE(quantizer.nDimension > 0);
  REQUIRE(quantizer.threshold > 0);
  REQUIRE(quantizer.maxRuns > 0);
  REQUIRE(quantizer.maxZeroRuns > 0);
  REQUIRE(quantizer.perturbation > 0);
}

TEST_CASE("LGBsplit run()", "[]") {
  LGBsplit<float> quantizer;
  std::vector<float> signal;
  SECTION("not enought signal points") {
    signal         = {1, 0, 2, 0};
    quantizer.rate = 1;
    quantizer.vectorize(signal);
    CHECK_THROWS(quantizer.run());
  }
  SECTION("clustering exit with positive status") {
    signal = {
        1, 0, 2, 0, 3, 0, 4, 0,
        1, 1, 2, 1, 3, 1, 4, 1,
        1, 2, 2, 2, 3, 2, 4, 2,
        1, 3, 2, 3, 3, 3, 4, 3,
        1, 4, 2, 4, 3, 4, 4, 4,

        7, 0, 8, 0, 9, 0, 10, 0,
        7, 1, 8, 1, 9, 1, 10, 1,
        7, 2, 8, 2, 9, 2, 10, 2,
        7, 3, 8, 3, 9, 3, 10, 3,
        7, 4, 8, 4, 9, 4, 10, 4};
    quantizer.rate         = 1;
    quantizer.perturbation = 0.1;
    quantizer.vectorize(signal);
    REQUIRE(quantizer.run() > 0);
  }
}