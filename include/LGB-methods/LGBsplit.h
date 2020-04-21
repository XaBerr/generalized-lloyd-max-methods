#ifndef _LGB_SPLT
#define _LGB_SPLT

#include "LGB.h"

namespace LGBm {

template <typename T>
class LGBsplit : public LGB<T> {
 public:
  double perturbation;
  LGBsplit() : LGB<T>{}, perturbation{0.001} {};
  int run() {
    size_t N            = this->signal.size();
    size_t M            = this->nDimension * this->rate;
    size_t nCodevectors = pow(2, M);
    vPoints<T> centroids;
    int status;
    Point<T> temp(this->nDimension);
    Point<T> vp(this->nDimension);
    Point<T> vm(this->nDimension);
    double per = perturbation;

    if (N < nCodevectors)
      throw "The signal size must be >= 2 ^ (nDimension * rate)!";

    // init first centroid
    centroids.push_back(this->signal[(size_t)rand() % N]);
    for (size_t i = 0; i < M + 1; i++) {
      // LGB
      status = LGB<T>::run(centroids);
      // zero cluster check
      if (status <= 0)
        return status;
      // split
      if (i != M) {
        centroids = {};
        for (Point<T> v : this->codebook) {
          // random vector
          std::for_each(temp.begin(), temp.end(), [per](T& element) {
            element = ((double)rand() / (RAND_MAX)) * per;
          });
          for (size_t j = 0; j < v.size(); j++) {
            vp[j] = v[j] + temp[j];
            vm[j] = v[j] - temp[j];
          }
          centroids.push_back(vp);
          centroids.push_back(vm);
        }
      }
    }
    return 1;
  }
};

};  // namespace LGBm
#endif