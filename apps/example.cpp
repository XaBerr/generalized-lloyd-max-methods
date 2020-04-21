#include <iostream>
#include <LGB-methods.h>
using namespace std;
using namespace LGBm;

int main() {
  LGBrandom<float> qRandom;
  LGBsplit<float> qSplit;
  std::vector<float> signal;
  int status;
  signal = {
      1, 0, 2, 0, 3, 0, 4, 0,
      1, 1, 2, 1, 3, 1, 4, 1,
      1, 2, 2, 2, 3, 2, 4, 2,
      1, 3, 2, 3, 3, 3, 4, 3,
      1, 4, 2, 4, 3, 4, 4, 4,

      7, 0, 8, 0, 9, 0, 10, 0,
      7, 1, 8, 1, 9, 1, 10, 1,
      7, 2, 8, 2, 9, 2, 10, 2,
      7, 3, 8, 3, 9, 3, 10, 3,
      7, 4, 8, 4, 9, 4, 10, 4};

  cout << "LGB-random quantizer codebook:" << endl;
  qRandom.rate       = 1;
  qRandom.nDimension = 2;
  qRandom.vectorize(signal);
  status = qRandom.run();
  cout << "With exit status: " << status << endl;
  qRandom.printVectorPoints(qRandom.codebook);

  cout << "LGB-split quantizer codebook:" << endl;
  qSplit.rate       = 1;
  qSplit.nDimension = 2;
  qSplit.vectorize(signal);
  status = qSplit.run();
  cout << "With exit status: " << status << endl;
  qSplit.printVectorPoints(qSplit.codebook);
}