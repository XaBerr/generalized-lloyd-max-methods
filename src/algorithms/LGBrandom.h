#ifndef _LGB_RANDOM
#define _LGB_RANDOM

#include "LGB.h"

template <typename T>
class LGBrandom {
  size_t rate;
  size_t nDimension;
  std::vector<T> data;

 public:
  LGBrandom(size_t _rate, size_t _nDimension) : rate{_rate}, nDimension{_nDimension} {};
  void setData(const std::vector<T>& _data) {
    data = _data;
  }
  T getData() const {
    return data;
  }
  void run() {
  }
};

#endif