#ifndef _LGB_SPLT
#define _LGB_SPLT

#include "LGB.h"

namespace LGBm {

template <typename T>
class LGBsplit : public LGB<T> {
 public:
  LGBsplit() : LGB<T>{} {};
  int run() {
    return 0;
  }
};

};  // namespace LGBm
#endif