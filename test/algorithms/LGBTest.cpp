#include "../../src/include.h"
#include "../catch.hpp"
using namespace LGBm;

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
  Point<float> signal{0, 0.5, 0.25};
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
  Point<float> signal;
  vPoints<float> initialPoints;
  Point<float> temp;
  quantizer.nDimension = 2;
  SECTION("signal no elements") {
    quantizer.vectorize(signal);
    quantizer.rate = 2;
    CHECK_THROWS(quantizer.run(initialPoints));
  }

  signal = {1, 2, 3, 0.7};
  quantizer.vectorize(signal);
  SECTION("initialPoints no elements") {
    quantizer.rate = 2;
    CHECK_THROWS(quantizer.run(initialPoints));
  }
  SECTION("initialPoints has size > 0") {
    temp           = {1, 2, 3, 0.7};
    initialPoints  = {temp};
    quantizer.rate = 1;
    CHECK_THROWS(quantizer.run(initialPoints));
  }
  SECTION("zero cluster") {
    temp           = {1, 2};
    initialPoints  = {temp, temp, temp, temp};
    quantizer.rate = 1;
    REQUIRE(quantizer.run(initialPoints) == -2);
  }
  SECTION("clustering exit with positive status") {
    signal         = {1, 0, 2, 0, 3, 0, 4, 0};
    initialPoints  = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};
    quantizer.rate = 1;
    quantizer.vectorize(signal);
    REQUIRE(quantizer.run(initialPoints) > 0);
    REQUIRE(quantizer.codebook.size() == 4);
    for (size_t i = 0; i < 4; i++) {
      REQUIRE(quantizer.codebook[i].size() == 2);
    }
  }
}

TEST_CASE("LGB distortion()", "[x,y]") {
  LGB<int> quantizer;
  // v = x - y = {0, -1}
  // v * v = 1
  REQUIRE(quantizer.distortion(std::vector<int>{0, 1}, std::vector<int>{0, 2}) == 1);
  // v = x - y = {0, -2}
  // v * v = 4
  REQUIRE(quantizer.distortion(std::vector<int>{0, 1}, std::vector<int>{0, 3}) == 4);
  // v = x - y = {0, 0}
  // v * v = 0
  REQUIRE(quantizer.distortion(std::vector<int>{0, 1}, std::vector<int>{0, 1}) == 0);
}

TEST_CASE("LGB centroid()", "[cluster]") {
  LGB<float> quantizer;
  vPoints<float> cluster;
  Point<float> result;
  Point<float> compare;
  SECTION("no elements") {
    cluster = {};
    CHECK_THROWS(quantizer.centroid(cluster));
  }
  SECTION("one element") {
    cluster = {{0, 1}};
    result  = quantizer.centroid(cluster);
    compare = {0, 1};
    REQUIRE(std::equal(result.begin(), result.end(), compare.begin()));
  }
  SECTION("two element equals") {
    cluster = {{0, 1}, {0, 1}};
    result  = quantizer.centroid(cluster);
    compare = {0, 1};
    REQUIRE(std::equal(result.begin(), result.end(), compare.begin()));
  }
  SECTION("two element differents") {
    cluster = {{0, 1}, {0, 3}};
    result  = quantizer.centroid(cluster);
    compare = {0, 2};
    REQUIRE(std::equal(result.begin(), result.end(), compare.begin()));
  }
}

TEST_CASE("LGB avgDistortion()", "[clusters,centroids]") {
  LGB<float> quantizer;
  std::vector<vPoints<float>> clusters = {{}, {}, {}};
  vPoints<float> centroids             = {{}, {}, {}};

  clusters[0]  = {{0, 1}, {0, 1}};
  clusters[1]  = {{0, 2}, {0, 2}};
  clusters[2]  = {{0, 3}, {0, 3}};
  centroids[0] = {0, 1};
  centroids[1] = {0, 2};
  centroids[2] = {0, 3};
  REQUIRE(quantizer.avgDistortion(clusters, centroids) == 0);
  // v = {0, 2}
  // v * v = 4
  // w = 4 + 4 + 4 + 4 = 16
  // 16 / 2 / 8
  clusters[2]  = {{0, 3}, {0, 3}, {0, 3}, {0, 3}};
  centroids[2] = {0, 1};
  REQUIRE(quantizer.avgDistortion(clusters, centroids) == 1);
}