#ifndef _LGB
#define _LGB

#include <cstdlib>
#include <vector>
#include <cmath>

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
  void run(const std::vector<std::vector<T>>& _initialPoints) {
    size_t N = signal.size();
    if (N == 0)
      return;
    size_t M = signal[0].size();
  }
};

#endif