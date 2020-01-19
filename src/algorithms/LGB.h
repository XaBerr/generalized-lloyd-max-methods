#ifndef _LGB
#define _LGB

#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <typeinfo>

namespace LGBm {

template <typename T>
using Point = std::vector<T>;

template <typename T>
using vPoints = std::vector<Point<T>>;

template <typename T>
class LGB {
 public:
  size_t rate;
  size_t nDimension;
  double threshold;
  size_t maxRuns;
  size_t maxZeroRuns;
  size_t dist;
  size_t error;
  vPoints<T> signal;
  vPoints<T> codebook;

  LGB() {
    rate        = 2;
    nDimension  = 2;
    threshold   = 0.01;
    maxRuns     = 10;
    maxZeroRuns = 5;
  }
  void vectorize(const Point<T>& _signal) {
    size_t N = _signal.size();
    if (N == 0)
      return;
    size_t N2  = ceil(((float)_signal.size()) / nDimension);
    signal     = {};
    size_t pos = 0;
    for (size_t i = 0; i < N2; i++) {
      Point<T> temp;
      for (size_t j = 0; j < nDimension; j++) {
        if (pos < N)
          temp.push_back(_signal[pos++]);
        else
          temp.push_back(0);
      }
      signal.push_back(temp);
    }
  }
  int run(const vPoints<T>& _initialPoints) {
    size_t N            = signal.size();
    size_t nCodevectors = pow(2, (nDimension * rate));
    bool noZeroClusters;
    T distances[N][nCodevectors];
    std::vector<vPoints<T>> clustersVal(nCodevectors);
    std::vector<std::vector<size_t>> clustersInd(nCodevectors);
    vPoints<T> centroids(nCodevectors);
    vPoints<T> centroidsOld(nCodevectors);
    size_t biggest = 0;
    size_t min;
    size_t D = SIZE_MAX;  // distortion
    size_t Dold;
    size_t E;  // error

    // checks
    if (N == 0)
      throw "The signal size must be > 0!";
    if (_initialPoints.size() != nCodevectors)
      throw "The number of initial point<T> must be the same of 2 * (nDimension * rate)!";
    if (_initialPoints[0].size() != nDimension)
      throw "The initial point<T> dimension must be the same of nDimension!";

    // main algorithm
    for (size_t run = 0; run < maxRuns; run++) {
      for (size_t zeroRun = 0; zeroRun < maxZeroRuns; zeroRun++) {
        // calculate the distances
        for (size_t i = 0; i < N; i++) {
          for (size_t j = 0; j < nCodevectors; j++) {
            distances[i][j] = distortion(signal[i], _initialPoints[j]);
          }
        }

        // find clusters
        for (size_t j = 0; j < nCodevectors; j++) {
          clustersVal[j] = {};
          clustersInd[j] = {};
        }
        for (size_t i = 0; i < N; i++) {
          min = 0;
          for (size_t j = 0; j < nCodevectors; j++)
            if (distances[i][j] < distances[i][min])
              min = j;
          clustersVal[min].push_back(signal[i]);
          // clustersInd[min].push_back(i);
        }

        // find biggest cluster
        biggest = 0;
        for (size_t j = 0; j < nCodevectors; j++)
          if (clustersVal[j].size() > clustersVal[biggest].size())
            biggest = j;
        if (clustersVal[biggest].size() == 0)
          return -1;

        // calculate centroid
        noZeroClusters = true;
        for (size_t j = 0; j < nCodevectors; j++) {
          if (clustersVal[j].size() == 0) {
            noZeroClusters = false;
            centroids[j]   = clustersVal[biggest][rand() % clustersVal[biggest].size()];
          } else {
            centroids[j] = centroid(clustersVal[j]);
          }
        }

        // break condition
        if (noZeroClusters)
          break;
      }
      // calculate the distortion
      Dold = D;
      D    = avgDistortion(clustersVal, centroids);
      if (D == 0)
        E = 0;
      else
        E = (D - Dold) / D;

      // break conditions
      if (!noZeroClusters)
        return -2;
      if (D >= Dold) {
        codebook = centroidsOld;
        dist     = D;
        error    = E;
        return 1;
      }
      if (threshold >= E) {
        codebook = centroids;
        dist     = D;
        error    = E;
        return 2;
      }
      centroidsOld = centroids;
    }
    return 0;
  }
  T distortion(const Point<T>& _x, const Point<T>& _y) const {
    T temp = 0;
    for (size_t i = 0; i < _x.size(); i++) {
      temp += (_x[i] - _y[i]) * (_x[i] - _y[i]);
    }
    return temp;
  }
  T avgDistortion(const std::vector<vPoints<T>>& _clusters, const vPoints<T>& _centroids) {
    T dist      = 0;
    T nElements = 0;
    for (size_t i = 0; i < _clusters.size(); i++) {
      nElements += _clusters[i].size();
      for (size_t j = 0; j < _clusters[i].size(); j++) {
        dist += distortion(_clusters[i][j], _centroids[i]);
      }
    }
    return dist / (nDimension * nElements);
  }
  Point<T> centroid(const vPoints<T>& _cluster) const {
    size_t N      = _cluster.size();
    Point<T> temp = {0};
    for (size_t j = 0; j < nDimension; j++) {
      for (size_t i = 0; i < N; i++) {
        temp[j] += _cluster[i][j];
      }
      temp[j] /= nDimension;
    }
    return temp;
  }
};

};  // namespace LGBm
#endif