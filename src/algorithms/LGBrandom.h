#ifndef _LGB_RANDOM
#define _LGB_RANDOM

#include "LGB.h"

namespace LGBm {

template <typename T>
class LGBrandom : public LGB<T> {
 public:
  LGBrandom() : LGB<T>{} {};
  int run() {
    size_t nCodevectors = pow(2, (this->nDimension * this->rate));
    size_t N            = this->signal.size();
    std::vector<size_t> indexes(nCodevectors);
    std::vector<size_t>::iterator it;
    vPoints<T> initialPoints(nCodevectors);
    if (N < nCodevectors)
      throw "The signal size must be >= 2 ^ (nDimension * rate)!";
    do {
      std::for_each(indexes.begin(), indexes.end(), [N](size_t& element) {
        element = (size_t)rand() % N;
      });
      it = std::unique(indexes.begin(), indexes.end());
      indexes.resize(std::distance(indexes.begin(), it));
    } while (indexes.size() != nCodevectors);

    for (size_t i = 0; i < nCodevectors; i++) {
      initialPoints[i] = this->signal[indexes[i]];
    }
    return LGB<T>::run(initialPoints);
  }
};

};  // namespace LGBm
#endif