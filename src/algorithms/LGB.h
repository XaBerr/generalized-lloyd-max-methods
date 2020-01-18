#ifndef _LGB
#define _LGB

#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <typeinfo>

template <typename T>
class LGB {
 public:
  size_t rate;
  size_t nDimension;
  double threshold;
  size_t maxRuns;
  size_t maxZeroRuns;
  std::vector<std::vector<T>> signal;

  LGB() {
    rate        = 2;
    nDimension  = 2;
    threshold   = 0.01;
    maxRuns     = 10;
    maxZeroRuns = 5;
  }
  void vectorize(const std::vector<T>& _signal) {
    size_t N = _signal.size();
    if (N == 0)
      return;
    size_t N2  = ceil(((float)_signal.size()) / nDimension);
    signal     = {};
    size_t pos = 0;
    for (size_t i = 0; i < N2; i++) {
      std::vector<T> temp;
      for (size_t j = 0; j < nDimension; j++) {
        if (pos < N)
          temp.push_back(_signal[pos++]);
        else
          temp.push_back(0);
      }
      signal.push_back(temp);
    }
  }
  bool run(const std::vector<std::vector<T>>& _initialPoints) {
    size_t N            = signal.size();
    size_t nCodevectors = pow(2, (nDimension * rate));
    bool noZeroClusters;
    T distances[N][nCodevectors];
    std::vector<std::vector<T>> clustersVal[nCodevectors];
    std::vector<size_t> clustersInd[nCodevectors];
    size_t min;
    size_t biggest = 0;
    std::vector<T> centroids[nCodevectors];

    // checks
    if (N == 0)
      throw "The signal size must be > 0!";
    if (_initialPoints.size() != nCodevectors)
      throw "The number of initial points must be the same of 2 * (nDimension * rate)!";
    if (_initialPoints[0].size() != nDimension)
      throw "The initial points dimension must be the same of nDimension!";
    // if (N == 0 || _initialPoints.size() != nCodevectors || _initialPoints[0].size() != nDimension)
    //   return false;

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
          return false;

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
      }
      // calculate the distortion
      // break conditions
    }
    return true;
  }
  T distortion(const std::vector<T>& _x, const std::vector<T>& _y) const {
    T temp = 0;
    for (size_t i = 0; i < _x.size(); i++) {
      temp += (_x[i] - _y[i]) * (_x[i] - _y[i]);
    }
    return temp;
  }
  std::vector<T> centroid(const std::vector<std::vector<T>>& _cluster) const {
    size_t N            = _cluster.size();
    std::vector<T> temp = {0};
    for (size_t j = 0; j < nDimension; j++) {
      for (size_t i = 0; i < N; i++) {
        temp[j] += _cluster[i][j];
      }
      temp[j] /= nDimension;
    }
    return temp;
  }
};

#endif