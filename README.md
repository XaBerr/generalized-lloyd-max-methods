# LGB-methods
In this repository there are various implementations of the Linde, Buzo, and Gray algorithm (generalize Lloyd-Max algorithm) for the calculation of vector quantizer. In particular these are the algorithms implemented until now:

- [x] LGB
- [x] LGB-random
- [x] LGB-split

## Requirements
<div style="background-color: #007bff; color:white; font-weight:bold; font-size:12px; display: inline-block; padding: 1px 4px; border-radius: 3px;">
c++11
</div>
<div style="background-color: #007bff; color:white; font-weight:bold; font-size:12px; display: inline-block; padding: 1px 4px; border-radius: 3px;">
CMake 3.14
</div>

## Installation
- **Manual**

  Download this repository:
  ```sh
  git clone git@github.com:XaBerr/LGB-methods.git
  ```
  and compile it running:
  ```sh
  rm build/ -rf;cmake -S . -B build;make -C build;
  ```

- **CMake module**

  Module data:
  ```java
  FetchContent_Declare(
    "LGB-methods"
    GIT_REPOSITORY https://github.com/XaBerr/LGB-methods.git
    GIT_TAG        1.0.0
  )
  ```

## Inclusion
All include file are avaiable in the `include` directory.
You can include each library individually:
```cpp
#include <LGB-methods/LGB.h>
#include <LGB-methods/LGBrandom.h>
#include <LGB-methods/LGBsplit.h>
using namespace LGBm;
```
or using the single include:
```cpp
#include <LGB-methods.h>
using namespace LGBm;
```

## Usage

#### LGB
First you need to initialize the quantizer.
```cpp
LGB<float> quantizer;
std::vector<float> signal = {1, 0, 2, 0, 3, 0, 4, 0};
std::vector<std::vector<float>> initialPoints  = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};
quantizer.rate = 1;
quantizer.nDimension = 2;
```

Then you can import the signal.
```cpp
quantizer.vectorize(signal);
```

In the end you can run the LGB algorithm and print the result.
```cpp
quantizer.run(initialPoints);
quantizer.printVectorPoints(quantizer.codebook);
```

#### LGB-random

To make this library work you must include this file.
```cpp
#include "LGB-methods/src/include.h"
using namespace LGBm;
```

First you must initialize the quantizer.
```cpp
LGBrandom<float> quantizer;
std::vector<float> signal = {1, 0, 2, 0, 3, 0, 4, 0};
std::vector<std::vector<float>> initialPoints  = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};
quantizer.rate = 1;
quantizer.nDimension = 2;
```

Then you can import the signal.
```cpp
quantizer.vectorize(signal);
```

In the end you can run the LGB algorithm and print the result.
```cpp
quantizer.run();
quantizer.printVectorPoints(quantizer.codebook);
```

#### LGB-split

To make this library work you must include this file.
```cpp
#include "LGB-methods/src/include.h"
using namespace LGBm;
```

First you must initialize the quantizer.
```cpp
LGBsplit<float> quantizer;
std::vector<float> signal = {1, 0, 2, 0, 3, 0, 4, 0};
std::vector<std::vector<float>> initialPoints  = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};
quantizer.rate = 1;
quantizer.nDimension = 2;
```

Then you can import the signal.
```cpp
quantizer.vectorize(signal);
```

In the end you can run the LGB algorithm and print the result.
```cpp
quantizer.run();
quantizer.printVectorPoints(quantizer.codebook);
```


## The LGB parameters

Here we have the parameters and theirs default values.
```cpp
// number of bit per sample
rate        = 2;

// the size of the vectors
nDimension  = 2;

// the maximum error allowed
threshold   = 0.01;

// max iteration limits
maxRuns     = 10;
maxZeroRuns = 5;
```
In addition for the LGB-split we have this parameter.
```cpp
// the size of the jump during the split
perturbation = 0.01;
```

## Exiting status for the run method

- **-2**: Generated a cluster with zero elements
- **-1**: Biggest cluster has zero size
- **+0**: Finish without reaching distortion or threshold limit
- **+1**: Stopped because distortion start increasing
- **+2**: Stopped because threshold reached

## Example
Also check out the example in `apps/example.cpp`.
