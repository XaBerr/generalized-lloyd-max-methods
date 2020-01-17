#include "../../src/include.h"
#include "../catch.hpp"

TEST_CASE("LGB LGB()", "[]") {
  LGB<int> quantizer;
  REQUIRE(quantizer.rate > 0);
  REQUIRE(quantizer.nDimension > 0);
  REQUIRE(quantizer.threshold > 0);
  REQUIRE(quantizer.maxRuns > 0);
  REQUIRE(quantizer.maxZeroRuns > 0);
}

TEST_CASE("LGB vectorize()", "[signal]") {
  LGB<float> quantizer;
  std::vector<float> signal{0, 0.5, 0.25};
  quantizer.nDimension = 2;
  quantizer.vectorize(signal);
  REQUIRE(quantizer.signal.size() == 2);
  REQUIRE(quantizer.signal[0].size() == 2);
  REQUIRE(quantizer.signal[0][0] == 0);
  REQUIRE(quantizer.signal[0][1] == 0.5);
  REQUIRE(quantizer.signal[1][0] == 0.25);
  REQUIRE(quantizer.signal[1][1] == 0);

  signal               = {1, 2, 3, 0.7};
  quantizer.nDimension = 2;
  quantizer.vectorize(signal);
  REQUIRE(quantizer.signal.size() == 2);
  REQUIRE(quantizer.signal[0].size() == 2);
  REQUIRE(quantizer.signal[0][0] == 1);
  REQUIRE(quantizer.signal[0][1] == 2);
  REQUIRE(quantizer.signal[1][0] == 3);
  REQUIRE(quantizer.signal[1][1] == 0.7f);
}

TEST_CASE("LGB run()", "[initialPoints]") {
  LGB<float> quantizer;
  std::vector<float> signal;
  std::vector<std::vector<float>> initialPoints;
  std::vector<float> temp;
  quantizer.nDimension = 2;
  SECTION("signal no elements") {
    quantizer.vectorize(signal);
    quantizer.rate = 2;
    REQUIRE(quantizer.run(initialPoints) == false);
  }

  signal = {1, 2, 3, 0.7};
  quantizer.vectorize(signal);
  SECTION("initialPoints no elements") {
    quantizer.rate = 2;
    REQUIRE(quantizer.run(initialPoints) == false);
  }
  SECTION("initialPoints wrong nCodevectors") {
    temp           = {1, 2};
    initialPoints  = {temp, temp};
    quantizer.rate = 1;
    REQUIRE(quantizer.run(initialPoints) == false);
  }
  SECTION("initialPoints has wrong nDimension") {
    temp           = {1, 2, 3, 0.7};
    initialPoints  = {temp};
    quantizer.rate = 1;
    REQUIRE(quantizer.run(initialPoints) == false);
  }
  SECTION("signal no elements") {
    temp           = {1, 2};
    initialPoints  = {temp};
    quantizer.rate = 1;
    REQUIRE(quantizer.run(initialPoints) == false);
  }
  SECTION("initialPoints is ok") {
    temp           = {1, 2};
    initialPoints  = {temp, temp, temp, temp};
    quantizer.rate = 1;
    REQUIRE(quantizer.run(initialPoints) == true);
  }
}