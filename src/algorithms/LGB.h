#ifndef _LGB
#define _LGB

#include <cstdlib>
#include <vector>

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
  void vectorize(std::vector<T> _signal) {
    size_t N = _signal.size();
    if (N == 0)
      return;
    if (N % nDimension != 0) {
      size_t pad = N - N % nDimension;
      for (int i = 0; i < pad; i++)
        _signal.push_back(0);
    }
    size_t N2  = _signal.size() / nDimension;
    signal     = {};
    size_t pos = 0;
    for (size_t i = 0; i < N2; i++) {
      /* code */
      std::vector<T> temp;
      for (size_t j = 0; j < nDimension; j++) {
        /* code */
        temp.push_back(_signal(pos++));
      }
      signal.push_back(temp);
    }
  }
  void run(std::vector<std::vector<T>> _initialPoints) {
    size_t N = signal.size();
    if (N == 0)
      return;
    size_t M = signal[0].size();
  }
};

#endif