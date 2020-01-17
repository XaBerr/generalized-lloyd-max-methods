#ifndef _LGB_SPLT
#define _LGB_SPLT

#include "LGB.h"

template <typename T>
class LGBsplit {
  size_t rate;
  size_t nDimension;
  std::vector<T> data;

 public:
  LGBsplit(size_t _rate, size_t _nDimension) : rate{_rate}, nDimension{_nDimension} {};
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